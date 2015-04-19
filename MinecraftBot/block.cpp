#include "block.h"

static const char walkableBlocksArray[] = { //This is the list of all the blocks and whether they are walkable through or not...
                                       //0 is walkable, 1 is solid block
                                       //2 is liquid, 3 is avoid because dangereous
                                       //4 doesn't exist, 5 is halfblock
                                       //6 is walkable through but you don't fall
                                   //   0   1   2   3   4   5   6   7   8   9
                                        0,  1,  1,  1,  1,  1,  0,  1,  2,  2, //0-9
                                        3,  3,  1,  1,  1,  1,  1,  1,  1,  1, //10-19
                                        1,  1,  1,  1,  1,  1,  1,  0,  0,  1, //20-29
                                        1,  0,  0,  1,  1,  1,  4,  0,  0,  0, //30-39
                                        0,  1,  1,  1,  5,  1,  1,  1,  1,  1, //40-49
                                        0,  3,  1,  1,  1,  0,  1,  1,  1,  0, //50-59
                                        1,  1,  1,  1,  1,  0,  0,  1,  0,  0, //60-69
                                        0,  1,  0,  1,  1,  0,  0,  0,  1,  1, //70-79
                                        1,  3,  1,  0,  1,  1,  1,  1,  1,  1, //80-89
                                        0,  1,  5,  0,  0,  1,  6,  1,  1,  1, //90-99
                                        1,  1,  1,  1,  0,  0,  0,  1,  1,  1, //100-109
                                        1,  6,  1,  1,  1,  0,  1,  1,  1,  0, //110-119
                                        1,  1,  1,  1,  1,  1,  5,  1,  1,  1, //120-129
                                        1,  0,  0,  1,  1,  1,  1,  1,  1,  1, //130-139
                                        1,  0,  0,  0,  1,  1,  1,  0,  0,  0, //140-149
                                        0,  5,  1,  1,  1,  1,  1,  0,  1,  1, //150-159
                                        1,  1,  1,  1,  1,  1,  1,  6,  1,  1, //160-169
                                        1,  6,  1,  1,  1,  0,  0,  0,  6,  1, //170-179
                                        1,  1,  5,  1,  1,  1,  1,  1,  1,  1, //180-189
                                        1,  1,  1,  1,  1,  1,  1,  1};        //190-197
const char* Block::walkableBlocks = walkableBlocksArray;
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
