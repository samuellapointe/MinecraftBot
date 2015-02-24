#include "loginstart.h"

LoginStart::LoginStart(MyTcpSocket * s, MainWindow * i_ui, const std::string &l)
{
    login = l;
    packetID = 0;
    socket = s;
    ui = i_ui;
    displayColor = QColor(150, 0 ,0);
}

LoginStart::~LoginStart()
{

}

void LoginStart::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    //server address
    QByteArray vectorLogin = Packet::packString(login);
    tmp.append(vectorLogin);

    //Call parent function to finish packing
    int length = Packet::sendPacket(Packet::packPacket(tmp, compressed));
    ui->displayPacket(false, packetID, length, displayColor, "Login Start");

}


