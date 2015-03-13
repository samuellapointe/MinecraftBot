#ifndef MAPCHUNKBULK_H
#define MAPCHUNKBULK_H

#include "packet.h"

class MapChunkBulk : Packet
{
public:
    MapChunkBulk(MyTcpSocket * socket, QByteArray &data, World * world);
    ~MapChunkBulk();
};

#endif // MAPCHUNKBULK_H
