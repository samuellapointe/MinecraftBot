#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "chunkcolumn.h"
#include <QByteArray>
#include <QDataStream>
#include <stdint.h>
#include "varint.h"
#include <cmath>

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
    Block getBlock(double x, double y, double z);
    void setBlock(int x, int y, int z, int i);
    std::map<std::pair<int, int>, ChunkColumn> chunkColumns;
private:
    int mod(int k, int n);

};

#endif // WORLD_H
