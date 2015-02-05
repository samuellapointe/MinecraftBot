/* packet.cpp
 * This class is used to define some attributes of a regular packet
 * */
#include "packet.h"

/* Packet format:
 * First, the size of the packet as a varint
 * then, the ID of the packet as a varint
 * finally, the data itself. */
QByteArray Packet::packPacket(const QByteArray &d, bool compress)
{
    QByteArray packet;

    if(compress)
    {
        //No compression
        appendVarint(packet, 0);
    }

    //ID
    appendVarint(packet, packetID);

    //Data
    packet.append(d);

    packetSize = packet.size();

    QByteArray packetFront;

    //Packet size
    appendVarint(packetFront, packetSize);

    packetFront.push_back(packet);

    return packetFront;
}

/* String format:
 * First, the length in bytes of the string as a varint
 * Then, the string itself */
QByteArray Packet::packString(const string &text)
{
    QByteArray tmp;
    appendVarint(tmp, text.size());
    tmp.append(text.c_str());

    return tmp;
}

//This function takes the adress to a byte array and adds a varint to it
void Packet::appendVarint(QByteArray &input, int value)
{
    //Buffer to give the function to fill
    uint8_t fillerBuffer[10];

    //Function itself
    int nbBytesEncoded = Varint::encode_unsigned_varint(fillerBuffer, value);
    for(int i = 0; i < nbBytesEncoded; i++)
    {
        input.append(fillerBuffer[i]);
    }
}

/*
//DECODING
int nbBytesDecoded;
int decodedValue = Varint::decode_unsigned_varint(fillerBuffer, nbBytesDecoded);
*/
