#include "handshake.h"

Handshake::Handshake(const uint8_t pV, const string &sA, const uint16_t sP, const uint8_t nS)
{
    protocolVersion = pV;
    serverAdress = sA;
    serverPort = sP;
    nextState = nS;
}

Handshake::~Handshake()
{

}

QByteArray Handshake::packPacket()
{
    //The data buffer
    QByteArray tmp;

    //protocol version (encode to varint)
    tmp.push_back(protocolVersion);

    //server address
    QByteArray bytesServerAdress = Packet::packString(serverAdress);
    tmp.append(bytesServerAdress);

    //server port
    tmp.append((const char*)&serverPort, sizeof(ushort));

    //next state
    tmp.append(nextState);

    //Call parent function to finish packing
    return(Packet::packPacket(tmp, 0));

}
