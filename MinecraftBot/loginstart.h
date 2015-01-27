#ifndef LOGINSTART_H
#define LOGINSTART_H

#include "packet.h"

class LoginStart : public Packet
{
public:
    LoginStart(const string &login);
    ~LoginStart();
    QByteArray packPacket();
private:
    string login;
};

#endif // LOGINSTART_H
