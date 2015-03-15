#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "chunkcolumn.h"
#include <QByteArray>
#include <QDataStream>
#include <stdint.h>
#include "varint.h"

class World
{
public:
    World();
    ~World();
    void addChunks(QByteArray data);
private:
    std::map<std::pair<int, int>, ChunkColumn> chunkColumns;
};

#endif // WORLD_H
