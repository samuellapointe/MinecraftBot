//Made this class to deal with everything related to encryption

#ifndef CRYPTMANAGER_H
#define CRYPTMANAGER_H

#include <QByteArray>
#include <rsa.h>

using namespace CryptoPP;

class CryptManager
{
public:
    CryptManager();
    ~CryptManager();
    void loadKey(QByteArray &key);
    RSA::PublicKey publicKey;
};

#endif // CRYPTMANAGER_H
