#ifndef KEEPALIVE_H
#define KEEPALIVE_H

#include "packet.h"

class KeepAlive : public Packet
{
public:
    KeepAlive(MyTcpSocket * socket, MainWindow * ui, QByteArray &data);
    ~KeepAlive();
    void sendPacket();
private:
    QByteArray data;
};

#endif // KEEPALIVE_H
