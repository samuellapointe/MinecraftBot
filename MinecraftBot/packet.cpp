/* packet.cpp
 * This class is used to define some attributes of a regular packet
 * */
#include "packet.h"

Packet::Packet()
{

}

Packet::Packet(MainWindow * i_ui, const QByteArray &d, bool compressed)
{
    //Some vars
    data = d;
    int nbBytesDecoded;
    uint8_t * buffer;
    ui = i_ui;

    //Data length
    buffer = (uint8_t*)data.data();
    packetSize = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
    data = data.right(data.length() - nbBytesDecoded); //Remove the bytes decoded so far
    if(compressed)
    {
        buffer = (uint8_t*)data.data();
        int uncompressedLength = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
        data = data.right(data.length() - nbBytesDecoded); //Remove the bytes decoded so far
        if(uncompressedLength != 0)
        {
            QByteArray tmp;
            tmp.append(static_cast<quint32>(uncompressedLength));
            tmp.append(data);
            data = qUncompress(tmp);
        }
        else
        {
            //ui->writeToConsole(data);
        }
    }
    //Next value is packet ID
    buffer = (uint8_t*)data.data();
    packetID = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
    data = data.right(data.length() - nbBytesDecoded); //Remove the bytes decoded so far
}

/* Packet format:
 * First, the size of the packet as a varint
 * then, the ID of the packet as a varint
 * finally, the data itself. */
QByteArray Packet::packPacket(const QByteArray &d, bool compressed)
{
    QByteArray packet;

    if(compressed)
    {
        //No compression
        appendVarint(packet, 0);
    }

    //ID
    appendVarint(packet, packetID);

    //Data
    packet.append(d);

    packetSize = packet.length();

    QByteArray packetFront;

    //Packet size
    appendVarint(packetFront, packetSize);

    packetFront.push_back(packet);

    return packetFront;
}

int Packet::sendPacket(const QByteArray &data)
{
    socket->write(data);
    return data.length();
}

/* String format:
 * First, the length in bytes of the string as a varint
 * Then, the string itself */
QByteArray Packet::packString(const std::string &text)
{
    QByteArray tmp;
    appendVarint(tmp, text.size());
    tmp.append(text.c_str());

    return tmp;
}

//This function takes the adress to a byte array and adds a varint to it
void Packet::appendVarint(QByteArray &input, int value)
{
    //Buffer to give the function to fill
    uint8_t fillerBuffer[10];

    //Function itself
    int nbBytesEncoded = Varint::encode_unsigned_varint(fillerBuffer, value);
    for(int i = 0; i < nbBytesEncoded; i++)
    {
        input.append(fillerBuffer[i]);
    }
}

