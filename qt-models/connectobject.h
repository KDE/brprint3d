#ifndef CONNECTOBJECT_H
#define CONNECTOBJECT_H
//Qt Includes
#include <QtCore/QString>

class ConnectObject
{
public:
    ConnectObject();
    void setSerialPort(QString s);
    void setTransmissionRate(int r);
    void setCacheSize(int s);
    void setResetOnConnect(bool b);
    void setPrintLog(bool b);
    QString getSerialPort();
    int getTransmissionRate();
    int getCacheSize();
    bool getResetOnConnect();
    bool getPrintLog();

private:
    QString serialPort;
    int transmissionRate;
    int cacheSize;
    bool resetOnConnect;
    bool printLog;
};

#endif // CONNECTOBJECT_H
