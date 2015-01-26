//CPP file for the Client class, which is the class handling most of the network stuff

#include "Client.h"
#include "mainwindow.h"

Client::Client(MainWindow * i_ui, const string &i_username, const string &i_password, const QString &i_ip, const int i_port)
{
    username = i_username;
    password = i_password;
    ip = i_ip;
    port = i_port;
    ui = i_ui;

}

Client::~Client()
{
}

void Client::startConnect()
{
    socket.ui = ui; //Give the socket the interface to write to
    socket.doConnect(ip, port);
}
