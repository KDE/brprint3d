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
#include "connectobject.h"

ConnectObject::ConnectObject()
{

}

void ConnectObject::setSerialPort(const QString &s)
{
    m_serialPort = s;
}

void ConnectObject::setTransmissionRate(const int &r)
{
    m_transmissionRate = r;
}

void ConnectObject::setCacheSize(const int &s)
{
    m_cacheSize = s;
}

void ConnectObject::setResetOnConnect(const bool &b)
{
    m_resetOnConnect = b;
}

void ConnectObject::setPrintLog(const bool &b)
{
    m_printLog = b;
}

QString ConnectObject::serialPort() const
{
    return m_serialPort;
}

int ConnectObject::transmissionRate() const
{
    return m_transmissionRate;
}

int ConnectObject::cacheSize() const
{
    return m_cacheSize;
}

int ConnectObject::resetOnConnect() const
{
    return m_resetOnConnect;
}

int ConnectObject::printLog() const
{
    return m_printLog;
}

