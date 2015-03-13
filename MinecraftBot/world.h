#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "chunkcolumn.h"

class World
{
public:
    World();
    ~World();
private:
    std::map<std::pair<int, int>, ChunkColumn> chunks;
};

#endif // WORLD_H
