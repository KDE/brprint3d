#include "bedobject.h"

bedObject::bedObject(int x, int y, int z)
{
    areaX = x;
    areaY = y;
    areaZ = z;
}

int bedObject::getX()
{
    return areaX;
}

int bedObject::getY()
{
    return areaY;
}

int bedObject::getZ()
{
    return areaZ;
}

double bedObject::getDesireTemp()
{
    return desireTemp;
}

double bedObject::getCurrTemp()
{
    return currTemp;
}

void bedObject::setDesireTemp(double t)
{
    desireTemp = t;
}

void bedObject::setCurrTemp(double t)
{
    currTemp = t;
}
