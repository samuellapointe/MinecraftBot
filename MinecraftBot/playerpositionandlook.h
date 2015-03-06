#ifndef PLAYERPOSITIONANDLOOK_H
#define PLAYERPOSITIONANDLOOK_H

#include "packet.h"

class PlayerPositionAndLook : public Packet
{
public:
    PlayerPositionAndLook(MyTcpSocket * socket, MainWindow * ui, QByteArray &data);
    ~PlayerPositionAndLook();
    double x;
    double y;
    double z;
    float yaw;
    float pitch;
    byte flags;
};

#endif // PLAYERPOSITIONANDLOOK_H
