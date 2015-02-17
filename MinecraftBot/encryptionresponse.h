#ifndef ENCRYPTIONRESPONSE_H
#define ENCRYPTIONRESPONSE_H

#include "packet.h"

class EncryptionResponse : public Packet
{
public:
    EncryptionResponse(MyTcpSocket * socket, MainWindow * ui, const QByteArray &sharedSecret, const QByteArray &token);
    ~EncryptionResponse();
    void sendPacket();
private:
    QByteArray sharedSecret;
    QByteArray token;
};

#endif // ENCRYPTIONRESPONSE_H
