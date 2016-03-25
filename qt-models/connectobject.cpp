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
#include "connectobject.h"

ConnectObject::ConnectObject()
{

}

void ConnectObject::setSerialPort(QString s)
{
    serialPort = s;
}

void ConnectObject::setTransmissionRate(int r)
{
    transmissionRate = r;
}

void ConnectObject::setCacheSize(int s)
{
    cacheSize = s;
}

void ConnectObject::setResetOnConnect(bool b)
{
    resetOnConnect = b;
}

void ConnectObject::setPrintLog(bool b)
{
    printLog = b;
}

QString ConnectObject::getSerialPort()
{
    return serialPort;
}

int ConnectObject::getTransmissionRate()
{
    return transmissionRate;
}

int ConnectObject::getCacheSize()
{
    return cacheSize;
}

bool ConnectObject::getResetOnConnect()
{
    return resetOnConnect;
}

bool ConnectObject::getPrintLog()
{
    return printLog;
}
