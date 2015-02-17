//CPP file for the Client class, which is the class handling most of the network stuff

#include "Client.h"
#include "mainwindow.h"
#include "handshake.h"
#include "loginstart.h"
#include "keepalive.h"
#include "encryptionrequest.h"
#include "encryptionresponse.h"

Client::Client(MainWindow * i_ui, const string &i_username, const string &i_password, const QString &i_ip, const int i_port)
{
    username = i_username;
    password = i_password;
    ip = i_ip;
    port = i_port;
    ui = i_ui;
    crypt = new CryptManager();
    currentState = HANDSHAKING;
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
        Handshake hs = Handshake(&socket, ui, 47, ip.toStdString(), port, 2);
        hs.sendPacket();
        LoginStart ls = LoginStart(&socket, ui, username);
        ls.sendPacket();

        //Switch to login phase
        currentState = LOGIN;
    }
}

void Client::decodePacket(QByteArray &data)
{
    if(encrypted)
    {
        data = crypt->decodeAES(data);
    }
    Packet p = Packet(data, compressionSet);
    handlePacket(p);
}

void Client::handlePacket(Packet &packet) //The big switch case of doom, to handle every packet
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
            ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(255, 75, 75), "Encryption request");
            enableEncryption(packet.data);
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
            currentState = PLAY;
            break;
        default:
            ui->writeToConsole("Unknown packet during LOGIN phase, ID " + QString::number(packet.packetID));
            break;
        }
        break;
    case PLAY:
        switch(packet.packetID)
        {
        default:
            ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(0,255,0), "Keep Alive");
            break;
        }
    }

    /*switch(packet.packetID)
    {
    case 0:
        if(compressionSet)
        {
            ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(150,150,255), "Keep alive");
            KeepAlive ka = KeepAlive(packet.data);
            socket.write(crypt->encodeAES(ka.packPacket()));
            ui->displayPacket(false, ka.packetID, ka.packetSize, QColor(150, 200, 200), "Keep alive");
        }
    case 1: //Encryption request
        if(!encrypted)
        {
            ui->displayPacket(true, packetID, packetSize, QColor(255, 100, 100), "Encryption request");
            EncryptionRequest er = EncryptionRequest(data);
            crypt->loadKey(er.publicKey);
            QByteArray hash = crypt->getHash(er.publicKey);
            EncryptionResponse er2 = EncryptionResponse(crypt->encodeRSA(crypt->sharedSecret.data()), crypt->encodeRSA(er.verifyToken));
            //Auth
            Authentificator auth = Authentificator();
            auth.ui = this->ui;
            auth.authentificate(username, password, hash);
            //Session

            //Finish
            socket.write(er2.packPacket());
            ui->displayPacket(false, packetID, packetSize, QColor(255, 100, 200), "Encryption response");
            encrypted = true;

        }
        break;
    case 3:
        {
            if(!compressionSet) //Set compression
            {
                compressionSet = true; //ID 3 sets compression in the login phase
                ui->displayPacket(true, packetID, packetSize, QColor(100,125,255), "Set compression!");
            }
            else //Keep alive
            {
                ui->displayPacket(true, packetID, packetSize, QColor(150,150,255), "Keep alive");
                KeepAlive ka = KeepAlive(data);
                socket.write(ka.packPacket());
                ui->displayPacket(false, ka.packetID, ka.packetSize, QColor(150, 200, 200), "Keep alive");
            }
        }
        break;
    default:
        if(ui->showUnknownPackets())
        {
            ui->displayPacket(true, packetID, packetSize);
        }
        break;
    }*/
}
void Client::enableEncryption(QByteArray &data)
{

    EncryptionRequest er = EncryptionRequest(data); //Decypher the data into an encryption request packet
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
    er2.sendPacket();
    encrypted = true;
}
