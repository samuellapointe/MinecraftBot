#include "playerpositionandlook.h"

PlayerPositionAndLook::PlayerPositionAndLook(MyTcpSocket * s, MainWindow * i_ui, QByteArray &d)
{
    data = d;
    packetID = 0;
    socket = s;
    ui = i_ui;

    QDataStream ds(data);

    ds >> x;
    ds >> y;
    ds >> z;
    ds >> yaw;
    ds >> pitch;
    ds >> flags;

}

PlayerPositionAndLook::~PlayerPositionAndLook()
{

}

