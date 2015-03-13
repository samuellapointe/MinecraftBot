#ifndef CHUNKCOLUMN_H
#define CHUNKCOLUMN_H

#include "chunk.h"

class ChunkColumn
{
public:
    ChunkColumn();
    ~ChunkColumn();
private:
    int position_x;
    int position_z;
    Chunk chunks[16];
};

#endif // CHUNKCOLUMN_H
