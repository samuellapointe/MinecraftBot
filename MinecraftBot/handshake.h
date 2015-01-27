#ifndef HANDSHAKE_H
#define HANDSHAKE_H

#include "packet.h"

class Handshake : public Packet
{
public:
    Handshake(const uint8_t protocolVersion, const string &serverAdress, const short serverPort, const uint8_t nextState);
    ~Handshake();
    vector<char> packPacket();
private:
    uint8_t protocolVersion;
    string serverAdress;
    short serverPort;
    uint8_t nextState;
};

#endif // HANDSHAKE_H
