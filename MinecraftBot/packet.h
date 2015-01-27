/* packet.h
 * Header file for the Packet class
 * */
#ifndef PACKET_H
#define PACKET_H

#include "varint.h"
#include <vector>
#include <string>

using namespace std;

class Packet
{
public:
    Packet(const uint32_t id, const vector<char> &data);
    ~Packet();
    vector<char> packPacket();
    vector<char> packString(const string &text);
private:
    uint32_t length;
    uint32_t packetID;
    vector<char> data;
};

#endif // PACKET_H
