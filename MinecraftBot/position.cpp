#include "position.h"

Position::Position()
{
    x = 0;
    y = 0;
    z = 0;
}

Position::Position(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Position::~Position()
{

}

Position Position::operator+(const Position& p)
{
    return Position(x + p.x, y + p.y, z + p.z);
}

Position Position::operator +(const Direction& d)
{
    Position direction = getPositionFromDirection(d);
    return Position(x + direction.x, y + direction.y, z + direction.z);
}

Position Position::operator-(const Position& p)
{
    return Position(x - p.x, y - p.y, z - p.z);
}

Position Position::operator -(const Direction& d)
{
    Position direction = getPositionFromDirection(d);
    return Position(x - direction.x, y - direction.y, z - direction.z);
}

Position Position::operator*(const Position& p)
{
    return Position(x * p.x, y * p.y, z * p.z);
}

Position Position::operator/(const Position& p)
{
    return Position(x / p.x, y / p.y, z / p.z);
}

Position Position::getFloored()
{
    return Position(floor(x), floor(y), floor(z));
}

bool Position::operator ==(const Position& p) const
{
    return (x == p.x && y == p.y && z == p.z);
}

bool Position::operator !=(const Position& p) const
{
    return !(x == p.x && y == p.y && z == p.z);
}

double Position::distance(Position other)
{
    double dX = abs(x - other.x);
    double dY = abs(y - other.y);
    double dZ = abs(z - other.z);
    return dX + dY + dZ;
}

Position Position::getPositionFromDirection(Direction d)
{
    switch(d)
    {
    case NORTH:
       return Position(0, 0, -1);
       break;
    case SOUTH:
       return Position(0, 0, 1);
       break;
    case EAST:
       return Position(1, 0, 0);
       break;
    case WEST:
       return Position(-1, 0, 0);
       break;
    case UP:
       return Position(0, 1, 0);
       break;
    case DOWN:
       return Position(0, -1, 0);
       break;
    case NONE: default:
        return Position(0, 0, 0);
        break;
    }
}

Direction Position::getDirectionFromPosition(Position p)
{
    p = normalize(p);
    if(p.x == 0 && p.y == 0 && p.z == -1)
    {
        return NORTH;
    }
    else if(p.x == 0 && p.y == 0 && p.z == 1)
    {
        return SOUTH;
    }
    else if(p.x == 1 && p.y == 0 && p.z == 0)
    {
        return EAST;
    }
    else if(p.x == -1 && p.y == 0 && p.z == 0)
    {
        return WEST;
    }
    else if(p.x == 0 && p.y == 1 && p.z == 0)
    {
        return UP;
    }
    else if(p.x == 0 && p.y == -1 && p.z == 0)
    {
        return SOUTH;
    }
    else
    {
        return NONE;
    }
}

Position Position::normalize(Position p)
{
    double before[3] = {p.x, p.y, p.z};
    double after[3];

    for(int i = 0; i < 3; i++)
    {
        if (before[i] > 0)
        {
            after[i] = 1;
        }
        else if (before[i] < 0)
        {
            after[i] = -1;
        }
        else
        {
            after[i] = 0;
        }
    }
    return Position(after[0], after[1], after[2]);
}
