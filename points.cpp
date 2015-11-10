/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 (c) 2015 BRPrint3D Authors 

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/

/* This file is a class of points in X,Y and Z Axis*/
#include "points.h"

Points::Points()
{

}
Points::~Points()
{
    delete this;
}

void Points::addPoint(float x, float y, float z) throw (QString)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Points::getPoint(float *x, float *y, float *z) throw (QString)
{
    (*x) = this->x;
    (*y) = this->y;
    (*z) = this->z;
}


