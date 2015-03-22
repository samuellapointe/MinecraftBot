#include "multiblockchange.h"

MultiBlockChange::MultiBlockChange(MyTcpSocket * s, QByteArray &d, World * world)
{
    data = d;
    packetID = 34;
    socket = s;

    world->updateBlocks(data);
}

MultiBlockChange::~MultiBlockChange()
{

}

