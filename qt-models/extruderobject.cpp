/*=====================================================================

 Br-Print3D, Open Source 3D Printing Host

 Copyright (C) 2016 Br-Print3D Authors

 This file is part of the Br-Print3D project

 Br-Print3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Br-Print3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Br-Print3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/
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
