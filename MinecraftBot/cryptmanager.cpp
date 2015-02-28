//Made this class to deal with everything related to encryption

#include "cryptmanager.h"

CryptManager::CryptManager()
{
    sharedSecret = "0123456789abcdef";
    byte IV[AES::BLOCKSIZE];
    memcpy(IV,sharedSecret.c_str(),16);

    AESDecryptor = new CFB_Mode<AES>::Decryption((byte*)sharedSecret.c_str(),(unsigned int)16,IV,1);
    AESEncryptor = new CFB_Mode<AES>::Encryption((byte*)sharedSecret.c_str(),(unsigned int)16,IV,1);

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

QByteArray CryptManager::getHash(QByteArray key)
{
    SHA1 sha1;
    std::string source = sharedSecret + key.toStdString();
    //std::string source = "simon";
    std::string hash;
    StringSource(source, true, new HashFilter(sha1, new HexEncoder(new StringSink(hash))));
    std::transform(hash.begin(), hash.end(), hash.begin(), ::tolower);
    hash = javaHexDigest(hash);

    return QByteArray(hash.c_str(), hash.length());
}

std::string CryptManager::javaHexDigest(std::string input)
{
    std::string binaryInput = hex_str_to_bin_str(input);
    bool negative = false;
    negative = binaryInput[0] == '1';
    if(negative) //NEGATIVE, apply two's complement
    {
        //First, invert 1 and 0
        for(size_t i = 0; i < binaryInput.length(); i++)
        {
            if(binaryInput[i] == '1') binaryInput[i] = '0';
            else binaryInput[i] = '1';
        }
        //Now add 1
        bool finished = false;
        int i = binaryInput.length() - 1;
        while(!finished)
        {
            if(binaryInput[i] == '0')
            {
                finished = true;
                binaryInput[i] = '1';
            }
            else
            {
                binaryInput[i] = '0';
            }
        }
    }
    //Convert back to hex
    input = bin_str_to_hex_str(binaryInput);
    //Remove leading 0s
    while(input[0] == '0')
    {
        input.erase(0,1);
    }
    //Add minus sing
    if(negative)
    {
        input.insert(0, "-");
    }
    return input;
}

std::string CryptManager::decodeAES(QByteArray inputBytes)//Code taken from http://pastebin.com/MjvR0T98
{
    /* Decrypt Data */
    std::string input = inputBytes.toStdString();
    std::string output("");
    try
    {
        StringSource(input, true, new StreamTransformationFilter(*AESDecryptor, new StringSink(output)));
    }
    catch(CryptoPP::Exception)
    {

    }

    return output;
}

QByteArray CryptManager::encodeAES(QByteArray inputBytes) //Code taken from http://pastebin.com/MjvR0T98
{
    /* Encrypt Data */
    std::string input = inputBytes.toStdString();
    std::string output("");
    try
    {
        StringSource(input, true, new StreamTransformationFilter(*AESEncryptor, new StringSink(output)));
    }
    catch(CryptoPP::Exception)
    {

    }
    return output.data();
}

const char* CryptManager::hex_char_to_bin(char c) //Function taken on http://stackoverflow.com/questions/18310952/convert-strings-between-hex-format-and-binary-format
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default: return "0000";
    }
}

std::string CryptManager::hex_str_to_bin_str(const std::string& hex) //Function taken on http://stackoverflow.com/questions/18310952/convert-strings-between-hex-format-and-binary-format
{
    // TODO use a loop from <algorithm> or smth
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += hex_char_to_bin(hex[i]);
    return bin;
}

const char CryptManager::bin_to_hex_char(std::string bin)
{
    if(bin.compare("0000") == 0) return '0';
    if(bin.compare("0001") == 0) return '1';
    if(bin.compare("0010") == 0) return '2';
    if(bin.compare("0011") == 0) return '3';
    if(bin.compare("0100") == 0) return '4';
    if(bin.compare("0101") == 0) return '5';
    if(bin.compare("0110") == 0) return '6';
    if(bin.compare("0111") == 0) return '7';
    if(bin.compare("1000") == 0) return '8';
    if(bin.compare("1001") == 0) return '9';
    if(bin.compare("1010") == 0) return 'a';
    if(bin.compare("1011") == 0) return 'b';
    if(bin.compare("1100") == 0) return 'c';
    if(bin.compare("1101") == 0) return 'd';
    if(bin.compare("1110") == 0) return 'e';
    if(bin.compare("1111") == 0) return 'f';
    return '0';
}

std::string CryptManager::bin_str_to_hex_str(const std::string &bin)
{
    std::string hex;
    for(unsigned i = 0; i != bin.length(); i+=4)
       hex += bin_to_hex_char(bin.substr(i, 4));
    return hex;
}
