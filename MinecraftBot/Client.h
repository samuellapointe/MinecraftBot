//Header file for the Client class, which is the class handling most of the network stuff

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "mytcpsocket.h"

using std::string;

class MainWindow; //MainWindow includes this header file, so I have to use this to avoid a circular dependency
class Client
{
public:
    Client(MainWindow * i_ui, const string &i_username, const string &i_password, const QString &i_ip, const int i_port);
    ~Client();
    void startConnect();
    void decodePacket(QByteArray &data);
    void handlePacket(int packetID, int packetSize, QByteArray &data);
private:
    string username;
    string password;
    QString ip;
    int port;
    MainWindow * ui;
    MyTcpSocket socket;
    bool compressionSet; //Pour savoir si la compression à été activée
};

#endif // CLIENT_H
