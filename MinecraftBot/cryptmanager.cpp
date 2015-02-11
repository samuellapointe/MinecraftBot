//Made this class to deal with everything related to encryption

#include "cryptmanager.h"

CryptManager::CryptManager()
{

}

void CryptManager::loadKey(QByteArray &key)
{
    ByteQueue keyQueue;
    QByteArray test = key.toBase64();
    for(int i = 0; i < key.size(); i++)
    {
        keyQueue.Put((byte)key.at(i));
    }
    //Base64Decoder decoder2;
    /*Base64Decoder decoder;
    decoder.Attach(new Redirector(keyQueue));
    decoder.Put((const byte*)str.data(), str.length());
    decoder.MessageEnd();*/

    publicKey.BERDecode(keyQueue);
    CryptoPP::RSAES_PKCS1v15_Encryptor e(publicKey);

    AutoSeededRandomPool rng;
    std::string plain="RSA Encryption", cipher, recovered;
    /*StringSource ss1(plain, true,
        new PK_EncryptorFilter(rng, e,
            new StringSink(cipher)
       ) // PK_EncryptorFilter
    ); // StringSource*/
}

CryptManager::~CryptManager()
{

}

QByteArray CryptManager::encodeRSA(QByteArray data)
{

    return data;
}

