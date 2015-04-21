#include "chunkcolumn.h"

ChunkColumn::ChunkColumn()
{

}

ChunkColumn::~ChunkColumn()
{

}

ChunkColumn::ChunkColumn(int x, int z, unsigned short bit)
{
    position = Position(x, -1, z);
    bitmask = bit;
}

