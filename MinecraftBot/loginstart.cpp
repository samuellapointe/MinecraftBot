#include "loginstart.h"

LoginStart::LoginStart(const string &l)
{
    login = l;
}

LoginStart::~LoginStart()
{

}

vector<char> LoginStart::packPacket()
{
    //The data buffer
    vector<char> tmp;

    //server address
    vector<char> vectorLogin = Packet::packString(login);
    tmp.insert(tmp.end(),vectorLogin.begin(),vectorLogin.end());

    //Call parent function to finish packing
    return(Packet::packPacket(tmp));

}


