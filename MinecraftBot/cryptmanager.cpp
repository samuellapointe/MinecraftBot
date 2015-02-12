//Made this class to deal with everything related to encryption

#include "cryptmanager.h"

CryptManager::CryptManager()
{

}

void CryptManager::loadKey(QByteArray &key)
{
    //Transform QByteArray into ByteQueue
    ByteQueue keyQueue;
    QByteArray test = key.toBase64();
    for(int i = 0; i < key.size(); i++)
    {
        keyQueue.Put((byte)key.at(i));
    }

    sharedSecret = "0123456789abcdef"; //A very complex private key

    //Finish making the key and the encryptor
    publicKey.BERDecode(keyQueue);
    encryptor = CryptoPP::RSAES_PKCS1v15_Encryptor(publicKey);
}

CryptManager::~CryptManager()
{

}

QByteArray CryptManager::encodeRSA(QByteArray data)
{
    AutoSeededRandomPool rng;
    std::string plain, cipher, recovered;
    plain = data.toStdString();
    StringSource ss1(plain, true,
        new PK_EncryptorFilter(rng, encryptor,
            new StringSink(cipher)
       ) // PK_EncryptorFilter
    ); // StringSource
    QByteArray output = QByteArray(cipher.c_str(), cipher.length());
    return output;
}

