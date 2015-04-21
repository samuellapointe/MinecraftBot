#include "chunkcolumn.h"

ChunkColumn::ChunkColumn()
{

}

ChunkColumn::~ChunkColumn()
{

}

ChunkColumn::ChunkColumn(int x, int z, unsigned short bit)
{
    position_x = x;
    position_z = z;
    bitmask = bit;
}

