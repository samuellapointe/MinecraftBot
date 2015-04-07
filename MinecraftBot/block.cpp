#include "block.h"

Block::Block()
{
    type = 0;
    light = 0;
}

Block::Block(short _type)
{
    type = _type;
    light = 0;
}

Block::~Block()
{

}

unsigned short Block::getType()
{
    return (type >> 4);
}

unsigned short Block::getMetadata()
{
    return (type & 15);
}
