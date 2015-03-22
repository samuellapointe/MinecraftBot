#include "mapchunk.h"

MapChunk::MapChunk(MyTcpSocket * s, QByteArray &d, World * world)
{
    data = d;
    packetID = 33;
    socket = s;

    world->addChunk(data);
}

MapChunk::~MapChunk()
{

}

