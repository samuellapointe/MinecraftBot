/* varint.cpp
 * This class encode and decodes varints
 * Code taken from http://stackoverflow.com/questions/19758270/read-varint-from-linux-sockets
 * */
#include "varint.h"

uint32_t Varint::decode_unsigned_varint( const uint8_t *const data, int &decoded_bytes )
{
    int i = 0;
    uint64_t decoded_value = 0;
    int shift_amount = 0;

    do
    {
        decoded_value |= (uint32_t)(data[i] & 0x7F) << shift_amount;
        shift_amount += 7;
    } while ( (data[i++] & 0x80) != 0 );

    decoded_bytes = i;
    return decoded_value;
}

int32_t Varint::decode_signed_varint( const uint8_t *const data, int &decoded_bytes )
{
    uint32_t unsigned_value = decode_unsigned_varint(data, decoded_bytes);
    return (int32_t)( unsigned_value & 1 ? ~(unsigned_value >> 1)
                                         :  (unsigned_value >> 1) );
}


// Encode an unsigned 64-bit varint.  Returns number of encoded bytes.
// 'buffer' must have room for up to 10 bytes.
int Varint::encode_unsigned_varint(uint8_t *const buffer, uint32_t value)
{
    int encoded = 0;

    do
    {
        uint8_t next_byte = value & 0x7F;
        value >>= 7;

        if (value)
            next_byte |= 0x80;

        buffer[encoded++] = next_byte;

    } while (value);


    return encoded;
}

// Encode a signed 64-bit varint.  Works by first zig-zag transforming
// signed value into an unsigned value, and then reusing the unsigned
// encoder.  'buffer' must have room for up to 10 bytes.
int Varint::encode_signed_varint(uint8_t *const buffer, int32_t value)
{
    uint32_t uvalue;

    uvalue = uint32_t( value < 0 ? ~(value << 1) : (value << 1) );

    return encode_unsigned_varint( buffer, uvalue );
}

int Varint::decodeVarint(QByteArray bytes, int &nbDecodedBytes)
{
    int decoded = 0;
    nbDecodedBytes = 0;
    bool decodingFinished = false;
    while(!decodingFinished)
    {
        char actualByte = bytes.at(nbDecodedBytes);

        decoded |= (actualByte & 127) << nbDecodedBytes++ * 7;

        if(nbDecodedBytes > 5)
        {
            //Something went wrong
            decoded = 0;
            nbDecodedBytes = 0;
            throw 1;
        }

        decodingFinished = ((actualByte & 128) != 128);

    }
    return decoded;
}
