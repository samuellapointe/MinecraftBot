#include "blockchange.h"

BlockChange::BlockChange(MyTcpSocket * s, QByteArray &d, World * world)
{
    data = d;
    packetID = 35;
    socket = s;

    world->updateBlock(data);
}

BlockChange::~BlockChange()
{

}

