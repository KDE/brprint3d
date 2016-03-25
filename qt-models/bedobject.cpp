#include "bedobject.h"

BedObject::bedObject(int x, int y, int z)
{
    areaX = x;
    areaY = y;
    areaZ = z;
}

int BedObject::getX()
{
    return areaX;
}

int BedObject::getY()
{
    return areaY;
}

int BedObject::getZ()
{
    return areaZ;
}

double BedObject::getDesireTemp()
{
    return desireTemp;
}

void BedObject::setDesireTemp(double t)
{
    desireTemp = t;
}
