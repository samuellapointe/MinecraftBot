#ifndef MULTIBLOCKCHANGE_H
#define MULTIBLOCKCHANGE_H

#include "packet.h"

class MultiBlockChange : public Packet
{
public:
    MultiBlockChange(MyTcpSocket * s, QByteArray &d, World * world);
    ~MultiBlockChange();
};

#endif // MULTIBLOCKCHANGE_H
