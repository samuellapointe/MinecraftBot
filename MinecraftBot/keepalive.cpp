#include "keepalive.h"

KeepAlive::KeepAlive(MyTcpSocket * s, MainWindow * i_ui, QByteArray &d)
{
    data = d;
    packetID = 0;
    socket = s;
    ui = i_ui;
    displayColor = QColor(0, 200 ,0);
}

KeepAlive::~KeepAlive()
{

}

void KeepAlive::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    tmp.append("0");

    //Call parent
    int length = Packet::sendPacket(Packet::packPacket(tmp, compressed));
    ui->displayPacket(false, packetID, length, displayColor, "Keep Alive");

}


