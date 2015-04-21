#ifndef CHUNKCOLUMN_H
#define CHUNKCOLUMN_H

#include "chunk.h"
#include "position.h"

class ChunkColumn
{
public:
    ChunkColumn();
    ChunkColumn(int position_x, int position_z, unsigned short bitmask);
    ~ChunkColumn();
    int position_x;
    int position_z;
    unsigned short bitmask;
    //Chunk chunks[16];
private:

};

#endif // CHUNKCOLUMN_H
