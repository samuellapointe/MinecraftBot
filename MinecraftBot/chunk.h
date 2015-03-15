#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"

class Chunk
{
public:
    Chunk();
    ~Chunk();
    Block blocks[16][16][16];
private:


};

#endif // CHUNK_H
