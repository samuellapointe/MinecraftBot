#ifndef ENCRYPTIONRESPONSE_H
#define ENCRYPTIONRESPONSE_H

#include "packet.h"

class EncryptionResponse : public Packet
{
public:
    EncryptionResponse(const QByteArray &sharedSecret, const QByteArray &token);
    ~EncryptionResponse();
    QByteArray packPacket();
private:
    QByteArray sharedSecret;
    QByteArray token;
};

#endif // ENCRYPTIONRESPONSE_H
