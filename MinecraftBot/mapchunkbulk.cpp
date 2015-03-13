#include "mapchunkbulk.h"

MapChunkBulk::MapChunkBulk(MyTcpSocket * s, QByteArray &d)
{
    data = d;
    packetID = 38;
    socket = s;

    bool skyLightSent = data.at(0);
    data.remove(0, 1);

    int nbBytesDecoded;
    uint8_t * buffer = (uint8_t*)data.data();
    int chunkColumnCount = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
    data.remove(0, nbBytesDecoded);

    QDataStream stream(data);
    int chunkX, chunkZ;
    stream >> chunkX;
    stream >> chunkZ;

    unsigned short bitmask;
    stream >> bitmask;



}

MapChunkBulk::~MapChunkBulk()
{

}

