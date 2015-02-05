#include "loginstart.h"

LoginStart::LoginStart(const string &l)
{
    login = l;
    packetID = 0;
}

LoginStart::~LoginStart()
{

}

QByteArray LoginStart::packPacket()
{
    //The data buffer
    QByteArray tmp;

    //server address
    QByteArray vectorLogin = Packet::packString(login);
    tmp.append(vectorLogin);

    //Call parent function to finish packing
    return(Packet::packPacket(tmp));

}

