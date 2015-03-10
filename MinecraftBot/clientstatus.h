#ifndef CLIENTSTATUS_H
#define CLIENTSTATUS_H

#include "packet.h"

class ClientStatus : public Packet
{
public:
    ClientStatus(MyTcpSocket * socket, MainWindow * ui, int actionID);
    ~ClientStatus();
    void sendPacket(bool compressed);
private:
    int actionID;
};

#endif // CLIENTSTATUS_H
