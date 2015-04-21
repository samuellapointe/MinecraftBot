#ifndef POSITION_H
#define POSITION_H

#include "direction.h"
#include "math.h"
#include <QHash>

class Position
{
public:
    Position();
    Position(double x, double y, double z);
    ~Position();
    double x;
    double y;
    double z;

    //Operators
    Position operator+(const Position& p);
    Position operator-(const Position& p);
    Position operator*(const Position& p);
    Position operator/(const Position& p);

    Position operator+(const Direction& d);
    Position operator-(const Direction& d);

    bool operator==(const Position& d) const;
    bool operator!=(const Position& d) const;

    //Functions
    Position getFloored();
    double distance(Position other);

    static Position getPositionFromDirection(Direction d);
    static Direction getDirectionFromPosition(Position p);
    static Position normalize(Position p); //ex: (-2, 0, 3.5) becomes (-1, 0, 1)

    int getXFloored();
    int getYFloored();
    int getZFloored();

};

inline uint qHash(const Position & pos) //Taken from http://stackoverflow.com/questions/29461703/how-can-i-store-a-3d-map-allowing-o1-random-access-c
{
    uint h = 0;
    uchar * p = (uchar*)&pos;
    for (uint i = 0; i < sizeof(Position); ++i)
    {
        h = 31 * h + p[i];
    }
    return h;
}

#endif // POSITION_H
