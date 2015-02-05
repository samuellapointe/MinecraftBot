#ifndef KEEPALIVE_H
#define KEEPALIVE_H

#include "packet.h"

class KeepAlive : public Packet
{
public:
    KeepAlive(QByteArray &data);
    ~KeepAlive();
    QByteArray packPacket();
private:
    QByteArray data;
};

#endif // KEEPALIVE_H
