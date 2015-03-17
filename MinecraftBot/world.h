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
    void addChunks(QByteArray data);
    Block getBlock(double x, double y, double z);
    std::map<std::pair<int, int>, ChunkColumn> chunkColumns;
private:

};

#endif // WORLD_H
