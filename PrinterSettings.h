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
