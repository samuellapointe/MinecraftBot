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
    data.remove(0, nbBytesDecoded);
    if(compressed)
    {
        buffer = (uint8_t*)data.data();
        int uncompressedLength = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
        QByteArray data2 = data;
        data.remove(0, nbBytesDecoded);
        if(uncompressedLength != 0)
        {
            data = uncompress(data);
            if(data.length() < 10000)
            {
                ui->writeToChat(data);
            }
        }
        else
        {
            //ui->writeToChat(data);
        }
    }
    //Next value is packet ID
    buffer = (uint8_t*)data.data();
    packetID = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
    data.remove(0, nbBytesDecoded);
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

QByteArray Packet::uncompress(QByteArray compressed) //Taken from http://wiki.vg/Chunk_data_decompressing_%28Zlib%29
{
    const int buffer_size = 100000;
    quint8 buffer[buffer_size];

    z_stream cmpr_stream;
    cmpr_stream.next_in = (unsigned char *)compressed.data();
    cmpr_stream.avail_in = compressed.size();
    cmpr_stream.total_in = 0;

    cmpr_stream.next_out = buffer;
    cmpr_stream.avail_out = buffer_size;
    cmpr_stream.total_out = 0;

    cmpr_stream.zalloc = Z_NULL;
    cmpr_stream.zfree = Z_NULL;
    cmpr_stream.opaque = Z_NULL;

    int status = inflateInit(&cmpr_stream);
    if (status != Z_OK)
    {
        ui->writeToConsole("cmpr_stream error!");
    }

    QByteArray uncompressed;
    do
    {
        cmpr_stream.next_out = buffer;
        cmpr_stream.avail_out = buffer_size;

        status = inflate( &cmpr_stream, Z_NO_FLUSH );

        if (status == Z_OK || status == Z_STREAM_END)
        {
            QByteArray chunk = QByteArray::fromRawData((char *)buffer, buffer_size - cmpr_stream.avail_out);
            uncompressed.append( chunk );
        }
        else
        {
            ui->writeToConsole("cmpr_stream error?" + QString::number(status) + " " + cmpr_stream.msg);
            inflateEnd(&cmpr_stream);
            break;
        }

        if (status == Z_STREAM_END)
        {
            inflateEnd(&cmpr_stream);
            break;
        }
   }
   while (cmpr_stream.avail_out == 0);

   return uncompressed;
}
