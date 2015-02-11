#include "encryptionresponse.h"

EncryptionResponse::EncryptionResponse(const QByteArray &ss, const QByteArray &t)
{
    sharedSecret = ss;
    token = t;
    packetID = 1;
}

EncryptionResponse::~EncryptionResponse()
{

}

QByteArray EncryptionResponse::packPacket()
{
    //The data buffer
    QByteArray tmp;

    //Length of shared secret
    appendVarint(tmp, sharedSecret.length());

    //Shared secret
    tmp.append(sharedSecret);

    //Length of verify token
    appendVarint(tmp, token.length());

    //verify token
    tmp.append(token);

    //Call parent
    return (Packet::packPacket(tmp));
}
