//Made this class to deal with everything related to encryption

#ifndef CRYPTMANAGER_H
#define CRYPTMANAGER_H

//#include "base64.h"
#include <rsa.h>
#include <osrng.h>
#include "hex.h"
//#include <files.h>
#include <QString>
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
    QByteArray getHash(QByteArray key);
private:
    //VARS
    RSA::PublicKey publicKey;
    RSAES<PKCS1v15>::Encryptor encryptor;
    //Functions
    std::string javaHexDigest(std::string input);

    //Convert hex string to binary string
    const char* hex_char_to_bin(char c);
    std::string hex_str_to_bin_str(const std::string& hex);

    //Convert binary string to hex string
    const char bin_to_hex_char(std::string bin);
    std::string bin_str_to_hex_str(const std::string& bin);


};

#endif // CRYPTMANAGER_H
