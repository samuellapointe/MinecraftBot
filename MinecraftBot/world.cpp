#include "world.h"

World::World()
{

}

World::~World()
{

}

void World::addChunks(QByteArray data)
{
    bool skyLightSent = data.at(0);
    data.remove(0, 1);

    int nbBytesDecoded;
    uint8_t * buffer = (uint8_t*)data.data();
    int chunkColumnCount = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
    data.remove(0, nbBytesDecoded);

    QDataStream stream(data);
    int chunkX, chunkZ;

    std::vector<ChunkColumn> chunkColumnsVector;

    for(int i = 0; i < chunkColumnCount; i++)
    {
        stream >> chunkX;
        stream >> chunkZ;

        unsigned short bitmask;
        stream >> bitmask;

        chunkColumnsVector.push_back(ChunkColumn(chunkX, chunkZ, bitmask));
    }

    for(int i = 0; i < chunkColumnCount; i++)
    {
        ChunkColumn actualColumn = chunkColumnsVector.at(i);
        //Blocks
        for (int j=0; j<16; j++) //The chunks inside a column
        {
            if (actualColumn.bitmask & (1 << j))
            {
                Chunk chunk = Chunk();

                //Blocks
                stream.setByteOrder(stream.LittleEndian); //Blocks are read in little-endian order
                for(int y = 0; y < 16; y++)
                {
                    for(int z = 0; z < 16; z++)
                    {
                        for(int x = 0; x < 16; x++)
                        {
                            unsigned short type;
                            stream >> type;
                            chunk.blocks[x][y][z].type = type;

                            unsigned short test = chunk.blocks[x][y][z].getType();
                        }
                    }
                }
                actualColumn.chunks[j] = chunk; //Set chunk

            }
        }
        //Lights
        stream.setByteOrder(stream.BigEndian);
        for (int j=0; j<16; j++) //The chunks inside a column
        {
            if (actualColumn.bitmask & (1 << j))
            {
                for(int y = 0; y < 16; y++)
                {
                    for(int z = 0; z < 16; z++)
                    {
                        for(int x = 0; x < 16; x+=2)
                        {
                            unsigned char light;
                            stream >> light;
                            actualColumn.chunks[j].blocks[x][y][z].light = (light >> 4); //Even index = high bits
                            actualColumn.chunks[j].blocks[x][y][z].light = (light & 15); //Odd index = low bits
                        }
                    }
                }
            }
        }
        //Skylight
        if(skyLightSent)
        {
            for (int j=0; j<16; j++) //The chunks inside a column
            {
                if (actualColumn.bitmask & (1 << j))
                {
                    for(int y = 0; y < 16; y++)
                    {
                        for(int z = 0; z < 16; z++)
                        {
                            for(int x = 0; x < 16; x+=2)
                            {
                                unsigned char light;
                                stream >> light;
                                actualColumn.chunks[j].blocks[x][y][z].skylight = (light >> 4); //Even index = high bits
                                actualColumn.chunks[j].blocks[x][y][z].skylight = (light & 15); //Odd index = low bits
                            }
                        }
                    }
                }
            }
        }
        chunkColumns.insert(std::make_pair(std::make_pair(actualColumn.position_x, actualColumn.position_z), actualColumn));
    }

}

Block World::getBlock(double x, double y, double z)
{
    //First, get the chunk column
    int chunkX = floor(x/16);
    int chunkY = floor(y/16);
    int chunkZ = floor(z/16);

    if(chunkColumns.find(std::make_pair(chunkX, chunkZ)) != chunkColumns.end())
    {
        ChunkColumn cc = chunkColumns.at(std::make_pair(chunkX, chunkZ));
        Chunk c = cc.chunks[chunkY];
        int blockX = abs(chunkX*16 - x);
        int blockY = abs(chunkY*16 - y);
        int blockZ = abs(chunkZ*16 - z);
        Block b = c.blocks[blockX][blockY][blockZ];
        return b;
    }
    else
    {
        Block b = Block();
        return b;
    }




}
