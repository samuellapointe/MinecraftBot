//Header file for the Client class, which is the class handling most of the network stuff

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "mytcpsocket.h"
#include "cryptmanager.h"
#include "authentificator.h"
#include "commandmanager.h"
#include "player.h"
#include "world.h"

using std::string;

enum State {HANDSHAKING, LOGIN, PLAY}; //Game state

class MainWindow; //MainWindow includes this header file, so I have to use this to avoid a circular dependency
class Packet;
class Client
{
public:
    Client(MainWindow * i_ui, const string &i_username, const string &i_password, const QString &i_ip, const int i_port);
    ~Client();
    void startConnect();
    void decodePacket(QByteArray data);
    void handlePacket(Packet &packet);
    void sendMessage(QString message);
    void movePlayer(Direction d, double distance);
    //Vars
    QString ip;
    CryptManager * crypt;
    CommandManager * commandManager;
    bool encrypted;
    bool compressionSet; //Pour savoir si la compression à été activée
    State currentState;
    Player * player;
    World * world;
private:
    //Vars
    string username;
    string password;
    int port;
    MainWindow * ui;
    MyTcpSocket socket;    int packetsSinceLastKA; //Packets received since the last keep alive, because it seems the server doesn't send enough to keep me alive!
    //Functions
    void authentificate();
    void enableEncryption(Packet * packet);


};

#endif // CLIENT_H
