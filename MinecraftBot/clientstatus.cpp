#include "clientstatus.h"

ClientStatus::ClientStatus(MyTcpSocket * s, MainWindow * i_ui, int a)
{
    packetID = 22;
    socket = s;
    ui = i_ui;
    actionID = a;
}

ClientStatus::~ClientStatus()
{

}

void ClientStatus::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    appendVarint(tmp, actionID);

    //Call parent
    Packet::sendPacket(Packet::packPacket(tmp, compressed));

}
