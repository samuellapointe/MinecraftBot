#include "positionf.h"

Positionf::Positionf()
{

}

Positionf::Positionf(Position p, int _fScore) : Position(p)
{
    fScore = _fScore;
}

bool Positionf::operator<(const Positionf pos) const
{
    if(fScore == pos.fScore)
    {
        return(x*10000+y*100+z)<(pos.x*10000 + pos.y*100 + pos.z);
    }
    else return fScore < pos.fScore;
}
