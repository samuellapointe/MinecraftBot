#ifndef ENCRYPTIONREQUEST_H
#define ENCRYPTIONREQUEST_H

#include "packet.h"

class EncryptionRequest : public Packet
{
public:
    EncryptionRequest(QByteArray &data);
    ~EncryptionRequest();

    //Vars from the packet
    int publicKeyLength;
    QByteArray publicKey;
    int verifyTokenLength;
    QByteArray verifyToken;
};

#endif // ENCRYPTIONREQUEST_H
