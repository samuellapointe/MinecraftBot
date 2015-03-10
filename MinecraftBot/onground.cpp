#include "onground.h"

OnGround::OnGround(MyTcpSocket * s, bool og)
{
    packetID = 3;
    socket = s;
    onGround = og;
}

OnGround::~OnGround()
{

}

void OnGround::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    tmp.append(onGround);

    //Call parent
    Packet::sendPacket(Packet::packPacket(tmp, compressed));

}
