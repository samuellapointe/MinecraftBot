#include "keepalive.h"

KeepAlive::KeepAlive(QByteArray &d)
{
    data = d;
    packetID = 0;
}

KeepAlive::~KeepAlive()
{

}

QByteArray KeepAlive::packPacket()
{
    //The data buffer
    QByteArray tmp;

    //The content of the keep alive
    uint8_t * buffer = (uint8_t*)data.data();
    int nbBytesDecoded;
    uint64_t decodedKeepAlive = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);

    //Packet::appendVarint(tmp, 0); //Tell the server it's not compressed
    Packet::appendVarint(tmp, decodedKeepAlive);

    //Call parent function to finish packing
    return(Packet::packPacket(tmp, false));

}


