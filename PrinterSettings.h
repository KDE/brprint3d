/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 Copyright (C) 2015 BRPrint3D Authors

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
#ifndef PRINTERSETTINGS_H
#define PRINTERSETTINGS_H
#include <QString>

class PrinterSettings
{

public:
    PrinterSettings();
    QString extruderTemperature="";
    QString bedTemperature="";
    QString extruderMAXTemp="";
    QString bedMAXTemp="";
    QString areaX="2";
    QString areaY="2";
    QString areaZ="2";
    QString rateMoviment="";
    QString extruderSpeedMM="";
    QString extruderSpeedS="";
    QString extruderRetraction="";
    QString extruderQnt="";
    QString connectionType="";
    QString transmissionRate="";
    QString firmwareType="";
    QString cacheSize="";
    QString connectionPort="";
    int resetOnConnect=0, resetOnEmergency=0, printLog=0, extrudersInUse=1;
    QString feedZ="";
    QString extruderMAXVol="";


};

#endif // PrinterSettings_H
