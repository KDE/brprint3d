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
#include "File_Queue.h"
#include "StringRepetierOps.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <thread>
#include <mutex>
#include <time.h>

#define WAIT_TIME 100

class Repetier
{
private:
    ASerial *arduino;
    int bufsize, *tempExtr, tempBed, nExtruders;
    double currentX, currentY, currentZ, currentE, maxX, maxY, maxZ, currentBedTemp, *currentExtrTemp;
    bool isPrintingRunning, terminate;
    bool isCommaDecimalMark;
    FILE *GCode;
    FQueue *LGCode, *log;
    std::string serialport;
    std::ofstream *logout;
    std::thread *printThread;
    std::mutex arduinoAccess, communicationBool;
    void printJob() throw (std::string);
    void saveLogFile();
public:
    Repetier(int baudrate, std::string serialport, int buffersize, double maxX, double maxY, double maxZ, bool resetWhenConnect, const bool isCommaDecimalMark) throw (std::string);
    ~Repetier();
    void closeFile();
    void openFile(std::string filepath, bool generateLog) throw (std::string);
    bool setBedTemp(int temp);
    bool setExtrTemp(int extrNo, int temp) throw (std::string);
    void extruderControl(double extrude, double atSpeed);
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
    bool isLogOn();
    bool isPrintJobRunning();
};

#endif /* defined(__KI_C____Repetier__) */
