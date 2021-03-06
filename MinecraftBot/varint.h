/* varint.h
 * Header file for the varint class
 * Code from http://stackoverflow.com/questions/19758270/read-varint-from-linux-sockets
 * */

#ifndef VARINT_H
#define VARINT_H

#include <stdint.h>
#include <iostream>
#include <QByteArray>

class Varint
{
public:
    static uint32_t decode_unsigned_varint( const uint8_t *const data, int &decoded_bytes );
    static int32_t decode_signed_varint( const uint8_t *const data, int &decoded_bytes );
    static int encode_unsigned_varint(uint8_t *const buffer, uint32_t value);
    static int encode_signed_varint(uint8_t *const buffer, int32_t value);
    static int decodeVarint(QByteArray, int &nbDecodedBytes);
};

#endif // VARINT_H
