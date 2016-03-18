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

void bedObject::setDesireTemp(double t)
{
    desireTemp = t;
}
