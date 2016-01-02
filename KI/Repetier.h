/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 (c) 2015 BRPrint3D Authors

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/

#ifndef __KI_C____Repetier__
#define __KI_C____Repetier__

#include "Arduino_Serial.h"
<<<<<<< HEAD
=======
#include "File_Queue.h"
>>>>>>> 51e8dce1efef8ac06a034c31a3f2dea23bf768be
#include "StringRepetierOps.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <thread>
#include <mutex>
<<<<<<< HEAD
#include <queue>
=======
>>>>>>> 51e8dce1efef8ac06a034c31a3f2dea23bf768be
#include <time.h>

#define WAIT_TIME 100

<<<<<<< HEAD
struct Repetier_object;

class Repetier
{
private:
    struct Repetier_object *_heap;
    void printJob() noexcept;
=======
class Repetier
{
private:
    ASerial *arduino;
    int bufsize, *tempExtr, tempBed, nExtruders;
    double currentX, currentY, currentZ, currentE, maxX, maxY, maxZ, currentBedTemp, *currentExtrTemp;
    double _printedFilament; //How much filament was used in meters.
    unsigned long _timeOfUsage; //Time of printer usage in seconds
    bool isPrintingRunning, terminate;
    bool isCommaDecimalMark;
    FILE *GCode;
    FQueue *LGCode, *log;
    std::string serialport;
    std::ofstream *logout;
    std::thread *printThread;
    std::mutex arduinoAccess, communicationBool;
    void printJob() throw (std::string);
>>>>>>> 51e8dce1efef8ac06a034c31a3f2dea23bf768be
    void saveLogFile();
public:
    Repetier(int baudrate, std::string serialport, int buffersize, double maxX, double maxY, double maxZ, bool resetWhenConnect, const bool isCommaDecimalMark) throw (std::string);
    ~Repetier();
    void closeFile();
<<<<<<< HEAD
    void openFile(std::string filepath, bool generateLog, std::string logpath) throw (std::string);
=======
    void openFile(std::string filepath, bool generateLog) throw (std::string);
>>>>>>> 51e8dce1efef8ac06a034c31a3f2dea23bf768be
    bool setBedTemp(int temp);
    bool setExtrTemp(int extrNo, int temp) throw (std::string);
    void extruderControl(double extrude, double atSpeed);
    bool setFeedRate(int percentage);
    bool setFlowRate(int percentage);
    bool setFanSpeed(int speed);
<<<<<<< HEAD
    bool startPrintJob();
    void stopPrintJob();
    void scramPrinter();
    void homeAxis(char Axis) throw (std::string);
    void homeAllAxis();
    void moveAxisToPos(char axis, double pos) throw (std::string);
    double getCurrentPos(char Axis) throw (std::string);
    double getMax(char Axis);
    int getNoOfExtruders();
    double getExtruderTemp(unsigned int extrNo) throw (std::string);
    int getTargetExtruderTemp(unsigned int extrNo) throw (std::string);
    double getBedTemp();
    int getTargetBedTemperature();
=======
    void startPrintJob(bool fromBegining);
    void stopPrintJob();
    void scramPrinter() throw (std::string);
    void homeAxis(char Axis) throw (std::string);
    void homeAllAxis();
    void moveAxisToPos(char axis, double pos) throw (std::string);
    double getCurrentE();
    double getCurrentXPos();
    double getCurrentYPos();
    double getCurrentZPos();
    double getMaxX();
    double getMaxY();
    double getMaxZ();
    int getNoOfExtruders();
    double getExtruderTemp(unsigned int extrNo) throw (std::string);
    double* getAllExtrudersTemp() throw (std::string);
    double getBedTemp();
>>>>>>> 51e8dce1efef8ac06a034c31a3f2dea23bf768be
    double getPrintedFilamentInMeters();
    unsigned long getTimeOfUsageInSec();
    bool isLogOn();
    bool isPrintJobRunning();
<<<<<<< HEAD
    bool hasPrinterDisconected();
    void turnATXOn();
    void turnATXOff();
=======
>>>>>>> 51e8dce1efef8ac06a034c31a3f2dea23bf768be
};

#endif /* defined(__KI_C____Repetier__) */
