#ifndef HANDSHAKE_H
#define HANDSHAKE_H

#include "packet.h"

class Handshake : public Packet
{
public:
    Handshake(MyTcpSocket * socket, MainWindow * ui, const uint8_t protocolVersion, const std::string &serverAdress, const uint16_t serverPort, const uint8_t nextState);
    ~Handshake();
    void sendPacket();
private:
    uint8_t protocolVersion;
    std::string serverAdress;
    uint16_t serverPort;
    uint8_t nextState;
};

#endif // HANDSHAKE_H
