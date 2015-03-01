//CPP file for the Client class, which is the class handling most of the network stuff

#include "Client.h"
#include "mainwindow.h"
#include "handshake.h"
#include "loginstart.h"
#include "keepalive.h"
#include "encryptionrequest.h"
#include "encryptionresponse.h"
#include "chatmessage.h"

#define PROTOCOLVERSION 47 //Version of the minecraft protocol (1.8)

Client::Client(MainWindow * i_ui, const string &i_username, const string &i_password, const QString &i_ip, const int i_port)
{
    username = i_username;
    password = i_password;
    ip = i_ip;
    port = i_port;
    ui = i_ui;
    crypt = new CryptManager();
    currentState = HANDSHAKING;

    packetsSinceLastKA = 0;
}

Client::~Client()
{
}

void Client::startConnect()
{
    compressionSet = false;
    encrypted = false;

    socket.ui = ui; //Give the socket the interface to write to
    socket.client = this;
    socket.doConnect(ip, port);

    if(socket.connectedBool)
    {
        //Send the two first packets necessary to connect
        Handshake hs = Handshake(&socket, ui, PROTOCOLVERSION, ip.toStdString(), port, 2);
        hs.sendPacket(compressionSet);
        LoginStart ls = LoginStart(&socket, ui, username);
        ls.sendPacket(compressionSet);

        //Switch to login phase
        currentState = LOGIN;
    }
}

void Client::decodePacket(QByteArray data)
{
    if(encrypted)
    {
        data = QByteArray::fromStdString(crypt->decodeAES(data));
    }
    Packet p = Packet(ui, data, compressionSet);
    handlePacket(p);
}

void Client::handlePacket(Packet &packet) //The big switch case of doom, to handle every packet
{
    if(packet.data.length() > 0)
    {
        switch(currentState) //Packet ID means different things depending on game state
        {
        case HANDSHAKING: //Always empty for the client as of Minecraft version 1.8.1, the client sends packets then switches to login
            break;
        case LOGIN:
            switch(packet.packetID)
            {
            case 0: //Disconnect
                //ui->writeToConsole("The server is kicking us out!");
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(0,0,0), "Disconnect");
                break;
            case 1: //Encryption request
                enableEncryption(packet);
                break;
            case 2: //Login Success
                ui->writeToConsole("Login successful");
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(255,150,150), "Login Success");
                currentState = PLAY;
                break;
            case 3: //Set compression
                ui->writeToConsole("Server enabled compression");
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(255,165,0), "Set Compression");
                compressionSet = true;
                break;
            default:
                ui->writeToConsole("Unknown packet during LOGIN phase, ID " + QString::number(packet.packetID));
                break;
            }
            break;
        case PLAY:
            packetsSinceLastKA++;
            switch(packet.packetID)
            {
            case 0: //Keep alive
                {
                    ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(100,255,100), "Keep Alive");
                    KeepAlive ka = KeepAlive(&socket, ui, packet.data);
                    ka.sendPacket(compressionSet);
                    packetsSinceLastKA = 0;
                }
                break;
            case 2: //Chat message
                {
                    ChatMessage cm = ChatMessage(&socket, ui, packet.data);
                }
                break;
            default:
                if(ui->showUnknownPackets())
                {
                    ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(255,255,255), "Unknown");
                }
                break;
            }
            if(packetsSinceLastKA > 150) //arbitrary value, timeout protection
            {
                packetsSinceLastKA = 0;
                KeepAlive ka = KeepAlive(&socket, ui, QByteArray::number(0));
                ka.sendPacket(compressionSet);
            }
        }
    }

}
void Client::enableEncryption(Packet packet)
{
    EncryptionRequest er = EncryptionRequest(packet.data, ui); //Decypher the data into an encryption request packet
    crypt->loadKey(er.publicKey); //Load the RSA public key into the cryptography manager
    QByteArray hash = crypt->getHash(er.publicKey); //Get the hash necessary for the encryption response
    EncryptionResponse er2 = EncryptionResponse(
                &socket,
                ui,
                crypt->encodeRSA(crypt->sharedSecret.data()),
                crypt->encodeRSA(er.verifyToken));
    //Auth
    Authentificator auth = Authentificator();
    auth.ui = this->ui;
    auth.authentificate(username, password, hash);
    //Session

    //Finish
    er2.sendPacket(compressionSet);
    encrypted = true;
}
