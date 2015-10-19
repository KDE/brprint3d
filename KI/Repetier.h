//
//  Repetier.h
//  KI-C++
//
//  Created by Ayrton Cavalieri de Almeida on 28/06/2015.
//  Copyright (c) 2015 Simple. All rights reserved.
//

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

class Repetier{
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
