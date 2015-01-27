/* packet.cpp
 * This class is used to define some attributes of a regular packet
 * */
#include "packet.h"

Packet::Packet(const uint32_t id, const vector<char> &d)
{
    packetID = id;
    data = d;
}

Packet::~Packet()
{

}

/* Packet format:
 * First, the size of the packet as a varint
 * then, the ID of the packet as a varint
 * finally, the data itself. */
vector<char> Packet::packPacket()
{
    uint8_t length = 4 + data.size(); //size of ID is 4
    uint32_t varintLength;
    Varint::encode_signed_varint(&length, varintLength);

    vector<char> tmp;
    tmp.push_back(varintLength);
    tmp.push_back(length);
    tmp.insert(tmp.end(), data.begin(), data.end());
    return tmp;
}

/* String format:
 * First, the length in bytes of the string as a varint
 * Then, the string itself */
vector<char> Packet::packString(const string text)
{
    uint8_t length = text.length(); //size of ID is 4
    uint32_t varintLength;
    Varint::encode_signed_varint(&length, varintLength);

    vector<char> tmp;
    tmp.push_back(varintLength);
    tmp.insert(tmp.end(),text.begin(),text.end());

    return tmp;
}
