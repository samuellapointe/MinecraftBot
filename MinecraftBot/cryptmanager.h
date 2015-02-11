//Made this class to deal with everything related to encryption

#ifndef CRYPTMANAGER_H
#define CRYPTMANAGER_H

//#include "base64.h"
#include <rsa.h>
#include <osrng.h>
//#include <files.h>
//#include <QString>
#include <QByteArray>
using namespace CryptoPP;

class CryptManager
{
public:
    //VARS
    QByteArray sharedSecret;

    //Functions
    CryptManager();
    ~CryptManager();
    void loadKey(QByteArray &key);
    QByteArray encodeRSA(QByteArray data);
private:
    //VARS
    RSA::PublicKey publicKey;
    //RSAES<PKCS1v15>::Encryptor encryptor;
};

#endif // CRYPTMANAGER_H
