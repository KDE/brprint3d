#ifndef PRINTERSETTINGS_H
#define PRINTERSETTINGS_H
#include <QString>
#include <ManualControlWidget.h>

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
    QString rateMoviment;
    QString extruderSpeedMM;
    QString extruderSpeedS;
    QString extruderRetraction;
    QString extruderQnt;
    QString connectionType;
    QString transmissionRate;
    QString firmwareType;
    QString cacheSize;
    QString connectionPort;
    int resetOnConnect, resetOnEmergency, printLog, extrudersInUse;
    QString feedZ;
    QString extruderMAXVol;


};

#endif // PrinterSettings_H
