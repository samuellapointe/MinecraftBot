#ifndef LOGINSTART_H
#define LOGINSTART_H

#include "packet.h"

class LoginStart : public Packet
{
public:
    LoginStart(MyTcpSocket * socket, MainWindow * ui, const std::string &login);
    ~LoginStart();
    void sendPacket(bool compressed);
private:
    std::string login;
};

#endif // LOGINSTART_H
