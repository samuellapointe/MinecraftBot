//CPP file for the Client class, which is the class handling most of the network stuff

#include "Client.h"
#include "mainwindow.h"
#include "handshake.h"
#include "loginstart.h"
#include "keepalive.h"
#include "encryptionrequest.h"
#include "encryptionresponse.h"
#include "chatmessage.h"
#include "sendchatmessage.h"
#include "playerpositionandlook.h"

#define PROTOCOLVERSION 47 //Version of the minecraft protocol (1.8)

Client::Client(MainWindow * i_ui, const string &i_username, const string &i_password, const QString &i_ip, const int i_port)
{
    username = i_username;
    password = i_password;
    ip = i_ip;
    port = i_port;
    ui = i_ui;
    crypt = new CryptManager();
    commandManager = new CommandManager(this, ui);
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
                ui->writeToConsole(packet.data);
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
            case 1: //Join game
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(223,205,247), "Join game");
                break;
            case 2: //Chat message
                {
                    ChatMessage cm = ChatMessage(&socket, ui, packet.data, commandManager);
                }
                break;
            case 3: //Time update
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(152,142,179), "Time Update");
                break;
            case 8: //Player position and look
                {
                    PlayerPositionAndLook ppal = PlayerPositionAndLook(&socket, ui, packet.data);
                    if(commandManager->waitingForCoords)
                    {
                        commandManager->setHome(ppal.x, ppal.y, ppal.z); //For the !sethome command
                    }
                }
                break;
            case 9: //Held item change
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(2,132,57), "Held item change");
                break;
            case 10: //Spawn position
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(87,171,30), "Spawn position");
                break;
            case 11: //Player abilities
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(55,142,62), "Player abilities");
                break;
            case 43: //Change game state
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(189,19,43), "Change game state");
                break;
            case 47: //Set slot
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(50,34,158), "Set slot");
                break;
            case 48: //Window items
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(123,34,216), "Window Items");
                break;
            case 55: //Statistics
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(18,239,159), "Statistics");
                break;
            case 59: //Scoreboard objective
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(180,40,208), "Scoreboard objective");
                break;
            case 60: //update score
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(156,142,68), "Update Score");
                break;
            case 61: //Scoreboard display
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(188,221,158), "Scoreboard display");
                break;
            case 62: //Teams
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(76,12,203), "Teams");
                break;
            case 63: //plugin message
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(95,188,145), "Plugin message");
                break;
            case 65: //Server difficulty
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(240,136,133), "Server difficulty");
                break;
            case 68: //World border
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(74,192,236), "World border");
                break;
            case 70: //Compression
                ui->writeToConsole("Server enabled compression");
                ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(255,165,0), "Set Compression");
                compressionSet = true;
                break;
            default:
                if(ui->showUnknownPackets())
                {
                    ui->displayPacket(true, packet.packetID, packet.packetSize, QColor(255,255,255), "Unknown");
                }
                break;
            }
            if(packetsSinceLastKA > 15000) //arbitrary value, timeout protection
            {
                packetsSinceLastKA = 0;
                KeepAlive ka = KeepAlive(&socket, ui, QByteArray::number(0));
                ka.sendPacket(compressionSet);
            }
            break;
        }
    }
    else
    {
        ui->writeToConsole("Packet rejected (size 0)");
    }

}
void Client::enableEncryption(Packet packet)
{
    EncryptionRequest er = EncryptionRequest(packet.data, ui); //Decypher the data into an encryption request packet
    crypt->loadKey(er.publicKey); //Load the RSA public key into the cryptography manager
    QByteArray hash = crypt->getHash(er.publicKey, er.serverID); //Get the hash necessary for the encryption response
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

void Client::sendMessage(QString message)
{
    //Cut the message in 100 bytes parts
    while(message.length() > 0)
    {
        SendChatMessage scm = SendChatMessage(&socket, ui, message.left(100));
        scm.sendPacket(compressionSet);
        message.remove(0, 100);
    }
}
