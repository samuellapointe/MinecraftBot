#include "block.h"

Block::Block()
{
    type = 0;
    light = 0;
}

Block::Block(unsigned short t, unsigned short l)
{
    type = t;
    light = l;
}

Block::~Block()
{

}

