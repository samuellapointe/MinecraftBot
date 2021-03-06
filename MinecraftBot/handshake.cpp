#include "handshake.h"

Handshake::Handshake(MyTcpSocket * s, MainWindow * i_ui, const uint8_t pV, const std::string &sA, const uint16_t sP, const uint8_t nS)
{
    protocolVersion = pV;
    serverAdress = sA;
    serverPort = sP;
    nextState = nS;
    packetID = 0;
    socket = s;
    ui = i_ui;
}

Handshake::~Handshake()
{

}

void Handshake::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    //protocol version (encode to varint)
    appendVarint(tmp, protocolVersion);

    //server address
    QByteArray bytesServerAdress = Packet::packString(serverAdress);
    tmp.append(bytesServerAdress);

    //server port
    tmp.append((const char*)&serverPort, sizeof(ushort));

    //next state
    appendVarint(tmp, nextState);

    //Call parent function to finish packing
    Packet::sendPacket(Packet::packPacket(tmp, compressed));
}

