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
        data.remove(0, 8); //Remove the two ints

        unsigned short bitmask;
        stream >> bitmask;

        data.remove(0, 2); //bitmask
        chunkColumnsVector.push_back(ChunkColumn(chunkX, chunkZ, bitmask));
    }

    for(int i = 0; i < chunkColumnCount; i++)
    {
        ChunkColumn actualColumn = chunkColumnsVector.at(i);
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
                            data.remove(0, 2);
                        }
                    }
                }
                actualColumn.chunks[j] = chunk; //Set chunk

            }
        }
        chunkColumns.insert(std::make_pair(std::make_pair(actualColumn.position_x, actualColumn.position_z), actualColumn));
        //chunkColumns[std::make_pair(0,0)];
        int wadwa = 1;
        //chunkColumns.insert(std::make_pair(actualColumn.position_x, actualColumn.position_z), actualColumn); //Insert the column into the world object
    }

}
