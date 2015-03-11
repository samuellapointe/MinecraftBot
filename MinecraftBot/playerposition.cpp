#include "playerposition.h"

PlayerPosition::PlayerPosition(MyTcpSocket * s, double x, double y, double z, bool og)
{
    packetID = 6;
    socket = s;
    position_x = x;
    position_y = y;
    position_z = z;
    onGround = og;
}

PlayerPosition::~PlayerPosition()
{

}

void PlayerPosition::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    appendDouble(tmp, position_x);
    appendDouble(tmp, position_y);
    appendDouble(tmp, position_z);
    appendFloat(tmp, 0);
    appendFloat(tmp, 0);
    tmp.append(onGround);

    //Call parent
    Packet::sendPacket(Packet::packPacket(tmp, compressed));

}


