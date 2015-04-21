#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "chunkcolumn.h"
#include <QByteArray>
#include <QDataStream>
#include <stdint.h>
#include "varint.h"
#include <cmath>
#include "direction.h"
#include "positionf.h"
#include <QHash>

class World
{
public:
    World();
    ~World();
    void addChunk(QByteArray data);
    void addChunks(QByteArray data);
    void updateBlock(QByteArray data);
    void updateBlocks(QByteArray data);
    void unloadChunk(int x, int z);
    Block getBlock(Position pos);
    void setBlock(Position pos, int i);
    bool canGo(Position pos, Direction d);
    std::map<std::pair<int, int>, ChunkColumn> chunkColumns;
    QHash<Position, Block> allBlocks;
private:
};

#endif // WORLD_H
