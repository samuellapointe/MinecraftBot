#ifndef ENCRYPTIONREQUEST_H
#define ENCRYPTIONREQUEST_H

#include "packet.h"

class EncryptionRequest : public Packet
{
public:
    EncryptionRequest(QByteArray data, MainWindow * ui);
    ~EncryptionRequest();

    //Vars from the packet
    int publicKeyLength;
    QByteArray publicKey;
    int verifyTokenLength;
    QByteArray verifyToken;
    QByteArray serverID;
};

#endif // ENCRYPTIONREQUEST_H
