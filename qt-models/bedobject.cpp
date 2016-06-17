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
#include "bedobject.h"

BedObject::BedObject(int x, int y, int z)
{
    m_areaX = x;
    m_areaY = y;
    m_areaZ = z;
}

double BedObject::getDesireTemp()
{
    return m_desireTemp;
}

void BedObject::setDesireTemp(double t)
{
    m_desireTemp = t;
}

int BedObject::areaX() const
{
    return m_areaX;
}

int BedObject::areaY() const
{
    return m_areaY;
}

int BedObject::areaZ() const
{
    return m_areaZ;
}

double BedObject::desireTemp() const
{
    return m_desireTemp;
}

double BedObject::currTemp() const
{
    return m_currTemp;
}

void BedObject::setAreaX(const int &x)
{
    m_areaX = x;
}

void BedObject::setAreaY(const int &y)
{
    m_areaY = y;
}

void BedObject::setAreaZ(const int &z)
{
    m_areaZ = z;
}

void BedObject::setdDesireTemp(const double &t)
{
    m_desireTemp = t;
}

//Dont know about this method
void BedObject::setCurrTemp(const double &t)
{
    m_currTemp = t;
}
