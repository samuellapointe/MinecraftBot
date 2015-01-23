//Header file for the Client class, which is the class handling most of the network stuff

#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using std::string;

class MainWindow; //MainWindow includes this header file, so I have to use this to avoid a circular dependency
class Client
{
public:
    Client(MainWindow * i_ui, const string &i_username, const string &i_password, const string &i_ip, const short i_port);
    ~Client();
private:
    string username;
    string password;
    string ip;
    short port;
    MainWindow * ui;
};

#endif // CLIENT_H
