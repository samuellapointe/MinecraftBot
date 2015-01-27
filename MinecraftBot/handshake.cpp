#include "handshake.h"

Handshake::Handshake(const uint8_t pV, const string &sA, const short sP, const uint8_t nS)
{
    packetID = 0;
    protocolVersion = pV;
    serverAdress = sA;
    serverPort = sP;
    nextState = nS;
}

Handshake::~Handshake()
{

}

vector<char> Handshake::packPacket()
{
    //The data buffer
    vector<char> tmp;

    //protocol version (encode to varint)
    uint32_t varintProtocolVersion;
    Varint::encode_signed_varint(&protocolVersion, varintProtocolVersion);
    tmp.push_back(varintProtocolVersion);

    //server address
    vector<char> vectorServerAdress = Packet::packString(serverAdress);
    tmp.insert(tmp.end(),vectorServerAdress.begin(),vectorServerAdress.end());

    //server port
    tmp.push_back(serverPort);

    //next state
    uint32_t varintNextState;
    Varint::encode_signed_varint(&nextState, varintNextState);
    tmp.push_back(varintNextState);

    //Call parent function to finish packing
    return(Packet::packPacket(tmp));

}
