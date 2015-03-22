#ifndef MAPCHUNK_H
#define MAPCHUNK_H

#include "packet.h"

class MapChunk : public Packet
{
public:
    MapChunk(MyTcpSocket * s, QByteArray &d, World * world);
    ~MapChunk();
};

#endif // MAPCHUNK_H
