#include "extruderobject.h"

ExtruderObject::ExtruderObject(int nExtruder ,int maxtemp, int mov, int ext, int fan)
{
    extruderNumber = nExtruder;
    maxTemp = maxtemp;
    movimentSpeed = mov;
    extrusionSpeed = ext;
    fanSpeed = fan;
}

void ExtruderObject::setMaxTemp(int t)
{
    maxTemp = t;
}

void ExtruderObject::setMovSpeed(int s)
{
    movimentSpeed = s;
}

void ExtruderObject::setExtrusionSpeed(int s)
{
    extrusionSpeed = s;
}

void ExtruderObject::setFanSpeed(int s)
{
    fanSpeed = s;
}

void ExtruderObject::setExtrusionQnt(double q)
{
    extrusionQnt = q;
}

int ExtruderObject::getMaxTemp()
{
    return maxTemp;
}

int ExtruderObject::getMovSpeed()
{
    return movimentSpeed;
}

int ExtruderObject::getExtrusionSpeed()
{
    return extrusionSpeed;
}

int ExtruderObject::getFanSpeed()
{
    return fanSpeed;
}

double ExtruderObject::getExtrusionQnt()
{
   return extrusionQnt;
}
