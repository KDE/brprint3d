/*=====================================================================

 BrPrint3D, Open Source 3D Printing Host

 Copyright (C) 2015 BRPrint3D Authors

 This file is part of the BrPrint3D project

 BrPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BrPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BrPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/
#ifndef EXTRUDEROBJECT_H
#define EXTRUDEROBJECT_H


class ExtruderObject
{
public:
    ExtruderObject(int nExtruder, int maxtemp, int mov, int ext, int fan);
    double currTemp;
    void setMaxTemp(int t);
    void setMovSpeed(int s);
    void setExtrusionSpeed(int s);
    void setFanSpeed(int s);
    void setExtrusionQnt(double q);
    int getMaxTemp();
    int getMovSpeed();
    int getExtrusionSpeed();
    int getFanSpeed();
    double getExtrusionQnt();

private:
    int maxTemp;
    int movimentSpeed;
    int extrusionSpeed;
    int fanSpeed;
    int extruderNumber;
    double extrusionQnt;
};

#endif // EXTRUDEROBJECT_H
