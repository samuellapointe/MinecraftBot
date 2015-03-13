#include "mapchunkbulk.h"

MapChunkBulk::MapChunkBulk(MyTcpSocket * s, QByteArray &d, World * world)
{
    data = d;
    packetID = 38;
    socket = s;

    world->addChunks(data);



}

MapChunkBulk::~MapChunkBulk()
{

}

