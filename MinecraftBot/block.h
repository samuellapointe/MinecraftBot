#ifndef BLOCK_H
#define BLOCK_H


class Block
{
public:
    Block();
    ~Block();
    short type;
    unsigned char light;
    unsigned char skylight;
    unsigned short getType();
    unsigned short getMetadata();

private:

};

#endif // BLOCK_H
