#ifndef PLAYERPOSITION_H
#define PLAYERPOSITION_H

#include "packet.h"

class PlayerPosition : public Packet
{
public:
    PlayerPosition(MyTcpSocket * socket, double x, double y, double z, bool onGround);
    ~PlayerPosition();
    void sendPacket(bool compressed);
    QByteArray getPacket(bool compressed);
private:
    double position_x;
    double position_y;
    double position_z;
    bool onGround;
};

#endif // PLAYERPOSITION_H
