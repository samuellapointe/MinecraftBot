#ifndef BLOCK_H
#define BLOCK_H


class Block
{
public:
    Block(unsigned short type, unsigned short light);
    ~Block();

private:
    unsigned short type;
    unsigned char light;
};

#endif // BLOCK_H
