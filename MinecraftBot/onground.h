#ifndef ONGROUND_H
#define ONGROUND_H

#include "packet.h"

class OnGround : public Packet
{
public:
    OnGround(MyTcpSocket * socket, bool og);
    ~OnGround();
    void sendPacket(bool compressed);
private:
    bool onGround;
};

#endif // ONGROUND_H
