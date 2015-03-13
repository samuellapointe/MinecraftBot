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

    for(int i = 0; i < chunkColumnCount; i++)
    {
        stream >> chunkX;
        stream >> chunkZ;
        data.remove(0, 8); //Remove the two ints

        unsigned short bitmask;
        stream >> bitmask;

        for (int j=0; j<16; j++) //The chunks inside a column
        {
            if (bitmask & (1 << j))
            {
                Block blocks[16][16][16];

                for(int z = 0; z < 16; z++)
                {
                    for(int x = 0; x < 16; x++)
                    {
                        for(int y = 0; y < 16; y++)
                        {
                            unsigned short type;
                            unsigned char light;
                            stream >> type;
                            stream >> light;
                            data.remove(0, 24);
                            blocks[x][y][z] = Block(type, light);
                        }
                    }
                }
            }
        }

    }

}
