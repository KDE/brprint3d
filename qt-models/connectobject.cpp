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
