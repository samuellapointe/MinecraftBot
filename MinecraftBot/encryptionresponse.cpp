#include "encryptionresponse.h"

EncryptionResponse::EncryptionResponse(MyTcpSocket * s, MainWindow * i_ui, const QByteArray &ss, const QByteArray &t)
{
    sharedSecret = ss;
    token = t;
    packetID = 1;
    socket = s;
    ui = i_ui;
    displayColor = QColor(100, 0, 0);
}

EncryptionResponse::~EncryptionResponse()
{

}

void EncryptionResponse::sendPacket(bool compressed)
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
    int length = Packet::sendPacket(Packet::packPacket(tmp, compressed));
    ui->displayPacket(false, packetID, length, displayColor, "Encryption Response");
}
