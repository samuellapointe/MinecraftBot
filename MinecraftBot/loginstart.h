#ifndef LOGINSTART_H
#define LOGINSTART_H

#include "packet.h"

class LoginStart : public Packet
{
public:
    LoginStart(const std::string &login);
    ~LoginStart();
    QByteArray packPacket();
private:
    std::string login;
};

#endif // LOGINSTART_H
