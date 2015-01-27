/* packet.cpp
 * This class is used to define some attributes of a regular packet
 * */
#include "packet.h"

/* Packet format:
 * First, the size of the packet as a varint
 * then, the ID of the packet as a varint
 * finally, the data itself. */
QByteArray Packet::packPacket(const QByteArray &d, int packetID)
{
    QByteArray tmp;
    tmp.append(packetID);
    tmp.append(d);

    int packetLength = tmp.size();
    tmp.push_front(packetLength);

    return tmp;
}

/* String format:
 * First, the length in bytes of the string as a varint
 * Then, the string itself */
QByteArray Packet::packString(const string &text)
{
    QByteArray tmp;
    tmp.append(text.size());
    tmp.append(text.c_str());

    return tmp;
}
