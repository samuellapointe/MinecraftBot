#ifndef BLOCKCHANGE_H
#define BLOCKCHANGE_H

#include "packet.h"

class BlockChange : public Packet
{
public:
    BlockChange(MyTcpSocket * s, QByteArray &d, World * world);
    ~BlockChange();
};

#endif // BLOCKCHANGE_H
