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

#include "Repetier.h"

struct Repetier_object{
    std::mutex _arduinoAccess;
    std::mutex _communicationLock;
    std::mutex _isPrintRunning;
    std::mutex _terminate;
    ASerial *_arduino;
    int *_tempExtr;
    double *_currentExtrTemp;
    FILE *_GCode;
    std::thread *_printThread;
    double _currentX;
    double _currentY;
    double _currentZ;
    double _currentE;
    double _maxX;
    double _maxY;
    double _maxZ;
    double _currentBedTemp;
    double _printedFilament;
    unsigned long _timeOfUsage;
    unsigned long _currentGCodeLine;
    std::queue<char*> _fQueue;
    std::queue<char*> _pLog;
    std::string _serialPort;
    std::ofstream _logout;
    int _bufsize;
    int _tempBed;
    int _nExtruders;
    //bool _isPrintingRunning;
    //bool _terminate;
    bool _isCommaDecimalMark;
    bool _disconected;
};

Repetier::Repetier(int baudrate, std::string serialport, int buffersize, double maxX, double maxY, double maxZ, const bool resetWhenConnect, const bool isCommaDecimalMark) throw (std::string)
{
    char format[16];
    char *vet;
    unsigned int pos;
    unsigned int days;
    unsigned int hours;
    unsigned int min;
    char send[buffersize];
    char serialAns[buffersize * 2];
    serialAns[0] = '\0';
    send[0] = '\0';
    format[0] = '\0';
    vet = NULL;
    pos = 0;
    days = 0;
    hours = 0;
    min = 0;    //Initialize all the variables on the stack.
    _heap = (struct Repetier_object*)malloc(sizeof(struct Repetier_object)); //Ask for the object space on the heap.
    if (_heap == NULL){ //If the space could not be allocated, throw exception.
        throw std::string("Repetier: Could not allocate and initialize memory space.");
    }
    try{
        _heap->_arduino = new ASerial(serialport, baudrate); //Try to open serial port.
    }catch (std::string exc){
        free(_heap);
        _heap = NULL;
        throw exc;
    }
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', buffersize) == -1){
            throw std::string("Repetier: Lost printer connection.");
        }
    }while (strstr(serialAns, "wait") == NULL); //Wait for Arduino to be ready.
    _heap->_isCommaDecimalMark = isCommaDecimalMark;
    _heap->_bufsize = buffersize;
    _heap->_maxX = maxX;
    _heap->_maxY = maxY;
    _heap->_maxZ = maxZ;
    _heap->_printThread = nullptr;
    _heap->_printedFilament = 0.0;
    _heap->_GCode = NULL;
    _heap->_currentX = 0.0;
    _heap->_currentY = 0.0;
    _heap->_currentZ = 0.0;
    _heap->_currentE = 0.0;
    _heap->_currentExtrTemp = NULL;
    _heap->_nExtruders = 0;
    _heap->_serialPort = serialport;
    _heap->_tempBed = 0;
    _heap->_tempExtr = NULL;
    _heap->_timeOfUsage = 0;
    _heap->_currentGCodeLine = 0;
    _heap->_disconected = false;
    if (resetWhenConnect == true){ //If user wants to reset when connect…
        sprintf(send, "M112\n");
        if (_heap->_arduino->writeStr(send) == -1) /*Send command to reset printer.*/{
            delete _heap->_arduino;
            free(_heap);
            _heap = NULL;
            throw std::string("Repetier: Lost printer connection.");
        }
#ifdef WAIT_TIME
        usleep(WAIT_TIME);
#endif
        do{
            if (_heap->_arduino->readUntil(serialAns, '\n', buffersize) == -1){
                delete _heap->_arduino;
                free(_heap);
                _heap = NULL;
                throw std::string("Repetier: Lost printer connection.");
            }
        }while (strstr(serialAns, "wait") == NULL); //Wait until the printer to be available.
    }
    sprintf(send, "M115\n"); //Asks for printer capabilities string.
    if (_heap->_arduino->writeStr(send) == -1){
        delete _heap->_arduino;
        free(_heap);
        _heap = NULL;
        throw std::string("Repetier: Lost printer connection.");
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        _heap->_arduino->readUntil(serialAns, '\n', buffersize * 2);
    }while (strstr(serialAns, "FIRMWARE") == NULL); //Waits for the answer.
    vet = strstr(serialAns, "EXTRUDER_COUNT:");
    if (vet != NULL){
        if (!sscanf(vet, "EXTRUDER_COUNT:%d", &_heap->_nExtruders)){
            delete _heap->_arduino;
            free(_heap);
            _heap = NULL;
            throw std::string("Repetier: Format error when acquiring number of extruders.");
        }
    }else{
        delete _heap->_arduino;
        free(_heap);
        _heap = NULL;
        throw std::string("Repetier: Could not get the number of extruders.");
    }
    if (_heap->_arduino->readUntil(serialAns, '\n', buffersize * 2) == -1){
        delete _heap->_arduino;
        free(_heap);
        _heap = NULL;
        throw std::string("Repetier: Lost printer connection.");
    }
    vet = strstr(serialAns, "Printing");
    if (vet != NULL){
        sscanf(serialAns, "Printed filament:%lf", &_heap->_printedFilament);
        sscanf(vet, "Printing time:%uld days %uld hours %uld", &days, &hours, &min);
        _heap->_timeOfUsage+=(days * 86400);
        _heap->_timeOfUsage+=(hours * 3600);
        _heap->_timeOfUsage+=(min * 60);
    }
    _heap->_tempExtr = (int*)malloc(_heap->_nExtruders * sizeof(int)); //Initialize the vector that will contain the target extruder temperatures.
    if (_heap->_tempExtr == NULL){
        delete _heap->_arduino;
        free(_heap);
        throw std::string("Repetier: Could not initialize Target Extruder Tempetarute vector.");
    }
    for (int i = 0; i < _heap->_nExtruders; i++){
        _heap->_tempExtr[i] = 0;
    }
    _heap->_currentExtrTemp = (double*)malloc(_heap->_nExtruders * sizeof(double)); //Initialize the vector that will contain the current extruder temperatures.
    if (_heap->_currentExtrTemp == NULL){
        delete _heap->_arduino;
        free(_heap->_tempExtr);
        free(_heap);
        throw std::string("Repetier: Could not initialize Current Extruder Tempetarute vector.");
    }
    for (int i = 0; i < _heap->_nExtruders; i++){
        _heap->_currentExtrTemp[i] = 0.0;
    }
    sprintf(send, "M105\n"); //Ask for current temperatures.
    if (_heap->_arduino->writeStr(send) == -1){
        free(_heap->_tempExtr);
        free(_heap->_currentExtrTemp);
        delete _heap->_arduino;
        free(_heap);
        throw std::string("Repetier: Lost printer connection.");
    }
#ifdef WAIT_TIM
    usleep(WAIT_TIME);
#endif
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', buffersize * 2) == -1){
            free(_heap->_tempExtr);
            free(_heap->_currentExtrTemp);
            delete _heap->_arduino;
            free(_heap);
            throw std::string("Repetier: Lost printer connection.");
        }
    }while (strstr(serialAns, "T:") == NULL); //Wait for answer…
    if (_heap->_nExtruders == 1){
        if (isCommaDecimalMark == true){
            pointDecimalMarkToComma(serialAns, buffersize * 2);
        }
        sscanf(serialAns, "T:%lf /%d", &_heap->_currentExtrTemp[0], &_heap->_tempExtr[0]);
    }else{
        if (isCommaDecimalMark == true){
            pointDecimalMarkToComma(serialAns, buffersize * 2);
        }
        for (int i = 0; i < _heap->_nExtruders; i++){
            sprintf(format, "T%d:", i);
            vet = strstr(serialAns, format);
            sprintf(format, "T%d:%%lf /%%d ", i);
            sscanf(vet, format, &_heap->_currentExtrTemp[i], &_heap->_tempExtr[i]);
        }
    }
    vet = strstr(serialAns, "B:"); //Looks for bed temperature.
    sscanf(vet, "B:%lf /%d ", &_heap->_currentBedTemp, &_heap->_tempBed);
    sprintf(send, "M114\n"); //Ask for current position.
    if (_heap->_arduino->writeStr(send) == -1){
        free(_heap->_tempExtr);
        free(_heap->_currentExtrTemp);
        delete _heap->_arduino;
        free(_heap);
        throw std::string("Repetier: Lost printer connection.");
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', buffersize) == -1){
            free(_heap->_tempExtr);
            free(_heap->_currentExtrTemp);
            delete _heap->_arduino;
            free(_heap);
            throw std::string("Repetier: Lost printer connection.");
        }
    }while (strstr(serialAns, "X:") == NULL);
    prepareStringToReceive(serialAns, buffersize);
    if (isCommaDecimalMark == true){
        pointDecimalMarkToComma(serialAns, buffersize);
    }
    sscanf(serialAns, "X:%lf Y:%lf Z:%lf E:%lf", &_heap->_currentX, &_heap->_currentY, &_heap->_currentZ, &_heap->_currentE);
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', buffersize) == -1){
            free(_heap->_tempExtr);
            free(_heap->_currentExtrTemp);
            delete _heap->_arduino;
            free(_heap);
            throw std::string("Repetier: Lost printer connection.");
        }
    }while (strstr(serialAns, "wait") == NULL); //Wait for Arduino to be idle.
}

Repetier::~Repetier()
{
    stopPrintJob();
    if (_heap->_printThread != nullptr){
        _heap->_printThread->detach();
        delete _heap->_printThread;
        _heap->_printThread = NULL;
    }
    delete _heap->_arduino;
    _heap->_arduino = nullptr;
    closeFile();
    free(_heap->_tempExtr);
    _heap->_tempExtr = NULL;
    free(_heap->_currentExtrTemp);
    _heap->_currentExtrTemp = NULL;
    free(_heap);
    _heap = NULL;
}

void Repetier::saveLogFile()
{
    char *printLogLine;
    if (_heap->_logout.is_open()){
        while (!_heap->_pLog.empty()){
            printLogLine = _heap->_pLog.front();
            (_heap->_logout) << printLogLine << '\n';
            _heap->_pLog.pop();
            free(printLogLine);
        }
        _heap->_logout.close();
    }
}

void Repetier::closeFile()
{
    char *fileLine;
    if (_heap->_GCode != NULL){
        while (!_heap->_fQueue.empty()){
            fileLine = _heap->_fQueue.front();
            _heap->_fQueue.pop();
            free(fileLine);
        }
        fclose(_heap->_GCode);
        _heap->_GCode = NULL;
        saveLogFile();
    }
}

void Repetier::openFile(std::string filepath, bool generateLog, std::string logpath) throw (std::string)
{
    char *instring;
    long timeOfTheDay;
    int p;
    char format[32];
    char logname[512];
    struct tm now;
    char temp[_heap->_bufsize];
    instring = NULL;
    if (_heap->_GCode != NULL){
        closeFile();
    }
    _heap->_GCode = fopen(filepath.c_str(), "rt"); //Open GCode
    if (_heap->_GCode == NULL){
        throw std::string("Repetier: Could not open GCode.");
    }
    sprintf(format, "%%%d[^\n]\n", _heap->_bufsize);
    while (fscanf(_heap->_GCode, format, temp) != EOF){
        if (temp[0] != ';'){
            for (p = 0; temp[p] != '\0'; p++){
                if (temp[p] == ';'){
                    temp[p] = '\n';
                    temp[p + 1] = '\0';
                    break;
                }
            }
            if (temp[p] == '\0'){
                temp[p] = '\n';
                temp[p + 1] = '\0';
            }
            instring = (char*)malloc((_heap->_bufsize + 3) * sizeof(char));
            if (instring == NULL){
                closeFile();
                throw std::string("Repetier: Error while opening GCode file, could not alocate enough memory.");
            }
            strcpy(instring, temp);
            _heap->_fQueue.push(instring);
        }
    }
    if (generateLog == true){
        timeOfTheDay = time(NULL);
        localtime_r(&timeOfTheDay, &now);
        sprintf(logname, "printerlog_%dY_%dM_%dD_%dH_%dM_%dS.log", (now.tm_year + 1900), (now.tm_mon + 1), \
                now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
        logpath += logname;
        _heap->_logout.open(logpath.c_str());
        if (!_heap->_logout.is_open()){
            closeFile();
            throw std::string("Repetier: Could not create log file.");
        }
    }
}

bool Repetier::setBedTemp(int temp)
{
    char *logtxt;
    int newBedTemp;
    int tries;
    bool OK;
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    tries = 0;
    send[0] = '\0';
    serialAns[0] = '\0';
    newBedTemp = 0;
    logtxt = NULL;
    OK = false;
    if (_heap->_tempBed == temp){
        return OK;
    }
    sprintf(send, "M140 S%d\n", temp);
    if (_heap->_isCommaDecimalMark == true){
        commaDecimalMarkToPoint(send, _heap->_bufsize);
    }
    _heap->_arduinoAccess.lock();
    if (_heap->_arduino->writeStr(send) == -1){
        _heap->_disconected = true;
        _heap->_arduinoAccess.unlock();
        return OK;
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize) == -1){
            _heap->_disconected = true;
            _heap->_arduinoAccess.unlock();
            return OK;
        }
        tries++;
    }while (serialAns[0] != 'T' && tries != 2);
    _heap->_arduinoAccess.unlock();
    if (_heap->_isCommaDecimalMark == true){
        pointDecimalMarkToComma(serialAns, _heap->_bufsize);
    }
    prepareStringToReceive(serialAns, _heap->_bufsize);
    if (sscanf(serialAns, "TargetBed:%d", &newBedTemp) != 0){
        _heap->_tempBed = newBedTemp;
        if (_heap->_logout.is_open() == true){
            logtxt = (char*)malloc(101 * sizeof(char));
            sprintf(logtxt, "Temperature of bed changed to %d oC.", newBedTemp);
            _heap->_pLog.push(logtxt);
        }
        OK = true;
    }
    return OK;
}

bool Repetier::setExtrTemp(int extrNo, int temp) throw (std::string)
{
    char *logtxt;
    int tempExt;
    int tries;
    bool OK;
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    tries = 0;
    OK = false;
    logtxt = NULL;
    tempExt = 0;
    send[0] = '\0';
    serialAns[0] = '\0';
    if (extrNo < _heap->_nExtruders && extrNo >= 0){
        if (_heap->_tempExtr[extrNo] == temp){
            return OK;
        }
        sprintf(send, "M104 S%d T%d\n", temp, extrNo);
        if (_heap->_isCommaDecimalMark == true){
            commaDecimalMarkToPoint(send, _heap->_bufsize);
        }
        _heap->_arduinoAccess.lock();
        _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
        usleep(WAIT_TIME);
#endif
        do{
            _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
            tries++;
        }while (serialAns[0] != 'T' && tries != 2);
        _heap->_arduinoAccess.unlock();
        prepareStringToReceive(serialAns, _heap->_bufsize);
        sprintf(send, "TargetExtr%d:%%d", extrNo); //'send' here contains the format to be read.
        if (sscanf(serialAns, send, &tempExt) != 0){
            _heap->_tempExtr[extrNo] = tempExt;
            if (_heap->_logout.is_open() == true){
                logtxt = (char*)malloc(101 * sizeof(char));
                sprintf(logtxt, "Temperature of extruder %d changed to %d oC.", extrNo, tempExt);
                _heap->_pLog.push(logtxt);
            }
            OK = true;
        }
    }else{
        throw std::string("Repetier: Invalid extruder number.");
    }
    return OK;
}

void Repetier::extruderControl(double extrude, double atSpeed)
{
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    send[0] = '\0';
    serialAns[0] = '\0';
    sprintf(send, "M82\n");
    _heap->_arduinoAccess.lock();
    _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
    }while (strstr(serialAns, "ok") == NULL);
    sprintf(send, "G1 E%.4lf F%.2lf\n", extrude, atSpeed);
    if (_heap->_isCommaDecimalMark == true){
        commaDecimalMarkToPoint(send, _heap->_bufsize);
    }
    _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
    }while (strstr(serialAns, "ok") == NULL);
    _heap->_arduinoAccess.unlock();
}

bool Repetier::setFeedRate(int percentage)
{
    bool OK;
    char i;
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    OK = false;
    send[0] = '\0';
    serialAns[0] = '\0';
    sprintf(send, "M220 S%d\n", percentage);
    _heap->_arduinoAccess.lock();
    _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    for (i = 0; i < 2; i++){
        _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
    }
    _heap->_arduinoAccess.unlock();
    if (strstr(serialAns, "Speed") != NULL){
        OK = true;
    }
    return OK;
}

bool Repetier::setFlowRate(int percentage)
{
    bool OK;
    char i;
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    OK = false;
    send[0] = '\0';
    serialAns[0] = '\0';
    sprintf(send, "M221 S%d\n", percentage);
    _heap->_arduinoAccess.lock();
    _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    for (i = 0; i < 2; i++){
        _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
    }
    _heap->_arduinoAccess.unlock();
    if (strstr(serialAns, "Flow") != NULL){
        OK = true;
    }
    return OK;
}

bool Repetier::setFanSpeed(int speed)
{
    bool OK;
    char i;
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    OK = false;
    send[0] = '\0';
    serialAns[0] = '\0';
    sprintf(send, "M106 S%d\n", speed);
    _heap->_arduinoAccess.lock();
    _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    for (i = 0; i < 2; i++){
        _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
    }
    _heap->_arduinoAccess.unlock();
    if (strstr(serialAns, "Fan") != NULL){
        OK = true;
    }
    return OK;
}

void Repetier::printJob() noexcept
{
    char *command;
    char *seek;
    char *logTxt;
    unsigned long control;
    char askCurrentPosition[8];
    char askCurrentTemperature[8];
    char format[16];
    int bufsize; //Contains _heap->_bufsize * 2.
    unsigned int tries; //Used to avoid a infinite loop and to read the extruders temperatures, if more than 1.
    char serialAns[_heap->_bufsize * 2];
    command = NULL;
    seek = NULL;
    logTxt = NULL;
    control = 0;
    sprintf(askCurrentPosition, "M114\n");
    sprintf(askCurrentTemperature, "M105\n");
    format[0] = '\0';
    bufsize = _heap->_bufsize * 2;
    serialAns[0] = '\0';
    if (_heap->_disconected == false){
        _heap->_isPrintRunning.lock();
        while (!_heap->_fQueue.empty()){
            if (_heap->_terminate.try_lock() == true){
                _heap->_terminate.unlock();
            }else{
                break;
            }
            command = _heap->_fQueue.front();
            _heap->_arduinoAccess.lock();
            if (_heap->_arduino->writeStr(command) == -1){
                _heap->_disconected = true;
                _heap->_arduinoAccess.unlock();
                break;
            }
#ifdef WAIT_TIME
            usleep(WAIT_TIME);
#endif
            for (tries = 0; tries != 5; tries++){
                if (_heap->_arduino->readUntil(serialAns, '\n', bufsize) == -1){
                    _heap->_disconected = true;
                    _heap->_arduinoAccess.unlock();
                    goto exitThreadMainLoop;
                }
                if (strstr(serialAns, "ok") != NULL || strstr(serialAns, "error") != NULL){
                    break;
                }
            }
            _heap->_arduinoAccess.unlock();
            if (_heap->_logout.is_open() == true){
                restoreSentString(command, _heap->_bufsize);
                prepareStringToReceive(serialAns, bufsize);
                logTxt = (char*)malloc((50 + (_heap->_bufsize * 3)) * sizeof(char));
                if (logTxt != NULL){
                    tries == 5 ? sprintf(logTxt, "GCode SLOC %lu (%s) Ans: %s", (control + 1), command, serialAns) :\
                    sprintf(logTxt, "GCode SLOC %lu (%s) Ans: Failed to get answer.", (control + 1), command);
                    _heap->_pLog.push(logTxt);
                }
            }
            _heap->_fQueue.pop();
            free(command);
            _heap->_arduinoAccess.lock();
            if (_heap->_arduino->writeStr(askCurrentTemperature) == -1){
                _heap->_disconected = true;
                _heap->_arduinoAccess.unlock();
                break;
            }
#ifdef WAIT_TIME
            usleep(WAIT_TIME);
#endif
            do{
                if (_heap->_arduino->readUntil(serialAns, '\n', bufsize) == -1){
                    _heap->_disconected = true;
                    _heap->_arduinoAccess.unlock();
                    goto exitThreadMainLoop;
                }
            }while (strstr(serialAns, "T:") == NULL);
            _heap->_arduinoAccess.unlock();
            prepareStringToReceive(serialAns, bufsize);
            if (_heap->_nExtruders == 1){
                sscanf(serialAns, "T:%lf /%d B:%lf /%d", &_heap->_currentExtrTemp[0], &_heap->_tempExtr[0], &_heap->_currentBedTemp, &_heap->_tempBed);
            }else{
                seek = strstr(serialAns, "B:");
                sscanf(seek, "B:%lf /%d", &_heap->_currentBedTemp, &_heap->_tempBed);
                for (tries = 0; tries < _heap->_nExtruders; tries++){
                    sprintf(format, "T%d:", tries);
                    seek = strstr(seek, format);
                    sprintf(format, "T%d:%%lf /%%d", tries);
                    sscanf(seek, format, &_heap->_currentExtrTemp[tries], &_heap->_tempExtr[tries]);
                }
            }
            _heap->_arduinoAccess.lock();
            if (_heap->_arduino->writeStr(askCurrentPosition) == -1){
                _heap->_disconected = true;
                _heap->_arduinoAccess.unlock();
                break;
            }
#ifdef WAIT_TIME
            usleep(WAIT_TIME);
#endif
            do{
                if (_heap->_arduino->readUntil(serialAns, '\n', bufsize) == -1){
                    _heap->_disconected = true;
                    _heap->_arduinoAccess.unlock();
                    goto exitThreadMainLoop;
                }
            }while (strstr(serialAns, "X:") == NULL);
            _heap->_arduinoAccess.unlock();
            prepareStringToReceive(serialAns, bufsize);
            sscanf(serialAns, "X:%lf Y:%lf Z:%lf E:%lf", &_heap->_currentX, &_heap->_currentY, &_heap->_currentZ, &_heap->_currentE);
            control++;
            std::this_thread::yield();
        }
exitThreadMainLoop:
        _heap->_isPrintRunning.unlock();
    }
}

bool Repetier::startPrintJob()
{
    stopPrintJob();
    if (_heap->_printThread != nullptr){
        _heap->_printThread->detach();
        delete _heap->_printThread;
    }
    try{
        _heap->_printThread = new std::thread(&Repetier::printJob, this);
    }catch (std::bad_alloc e){
        _heap->_printThread = nullptr;
        return false;
    }
    return true;
}

void Repetier::stopPrintJob()
{
    _heap->_terminate.lock();
    _heap->_isPrintRunning.lock();
    _heap->_terminate.unlock();
    _heap->_isPrintRunning.unlock();
}

void Repetier::scramPrinter()
{
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    send[0] = '\0';
    serialAns[0] = '\0';
    stopPrintJob();
    sprintf(send, "M112\n");
    _heap->_arduinoAccess.lock();
    if (_heap->_arduino->writeStr(send) == -1){
        _heap->_disconected = true;
        _heap->_arduinoAccess.unlock();
        return;
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize) == -1){
            _heap->_disconected = true;
            _heap->_arduinoAccess.unlock();
            return;
        }
    }while (strstr(serialAns, "wait") == NULL);
    _heap->_arduinoAccess.unlock();
}

void Repetier::homeAxis(char Axis) throw (std::string)
{
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    send[0] = '\0';
    serialAns[0] = '\0';
    if (Axis >= 'a' && Axis <= 'z'){
        Axis ^= 0x20;
    }
    if (Axis != 'X' && Axis != 'Y' && Axis != 'Z'){
        throw std::string("Repetier: Invalid Axis.");
    }
    sprintf(send, "G28 %c0\n", Axis);
    _heap->_arduinoAccess.lock();
    if (_heap->_arduino->writeStr(send) == -1){
        _heap->_disconected = true;
        _heap->_arduinoAccess.unlock();
        return;
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize) == -1){
            _heap->_disconected = true;
            _heap->_arduinoAccess.unlock();
            return;
        }
    }while (strstr(serialAns, "X:") != NULL);
    switch (Axis){
    case 'X':
        _heap->_currentX = 0;
        break;
    case 'Y':
        _heap->_currentY = 0;
        break;
    case 'Z':
        _heap->_currentZ = 0;
        break;
    default:
        break;
    }
    _heap->_arduinoAccess.unlock();
}

void Repetier::homeAllAxis()
{
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    send[0] = '\0';
    serialAns[0] = '\0';
    sprintf(send, "G28\n");
    _heap->_arduinoAccess.lock();
    if (_heap->_arduino->writeStr(send) == -1){
        _heap->_disconected = true;
        _heap->_arduinoAccess.unlock();
        return;
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize)){
            _heap->_disconected = true;
            _heap->_arduinoAccess.unlock();
            return;
        }
    }while (strstr(serialAns, "X:") != NULL);
    _heap->_currentX = 0;
    _heap->_currentY = 0;
    _heap->_currentZ = 0;
    _heap->_arduinoAccess.unlock();
}

void Repetier::moveAxisToPos(char Axis, double pos) throw (std::string)
{
    char *seek;
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    seek = NULL;
    send[0] = '\0';
    serialAns[0] = '\0';
    if (Axis >= 'a' && Axis <= 'z'){
        Axis ^= 0x20;
    }
    if (Axis != 'X' && Axis != 'Y' && Axis != 'Z'){
        throw std::string("Repetier: Invalid Axis.");
    }
    sprintf(send, "G1 %c%.3lf\n", Axis, pos);
    if (_heap->_isCommaDecimalMark == true){
        commaDecimalMarkToPoint(send, _heap->_bufsize);
    }
    _heap->_arduinoAccess.lock();
    if (_heap->_arduino->writeStr(send) == -1){
        _heap->_disconected = true;
        _heap->_arduinoAccess.unlock();
        return;
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        if (_heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize) == -1){
            _heap->_disconected = true;
            _heap->_arduinoAccess.unlock();
            return;
        }
    }while (strstr(serialAns, "ok") == NULL);
    sprintf(send, "M114\n");
    if (_heap->_arduino->writeStr(send) == -1){
        _heap->_disconected = true;
        _heap->_arduinoAccess.unlock();
        return;
    }
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
    }while (strstr(serialAns, "X:") == NULL);
    _heap->_arduinoAccess.unlock();
    if (_heap->_isCommaDecimalMark == true){
        pointDecimalMarkToComma(serialAns, _heap->_bufsize);
    }
    switch (Axis){
    case 'X':
        sscanf(serialAns, "X:%lf ", &_heap->_currentX);
        break;
    case 'Y':
        seek = strstr(serialAns, "Y:");
        sscanf(seek, "Y:%lf ", &_heap->_currentY);
        break;
    case 'Z':
        seek = strstr(serialAns, "Y:");
        sscanf(seek, "Z:%lf ", &_heap->_currentZ);
        break;
    default:
        break;
    }
}

double Repetier::getCurrentPos(char Axis) throw (std::string)
{
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize];
    send[0] = '\0';
    serialAns[0] = '\0';
    if (Axis >= 'a' && Axis <= 'z'){
        Axis ^= 0x20;
    }
    if (Axis != 'X' && Axis != 'Y' && Axis != 'Z'){
        throw std::string("Repetier: Invalid Axis.");
    }
    if (_heap->_isPrintRunning.try_lock() == true){
        sprintf(send, "M114\n");
        _heap->_arduinoAccess.lock();
        _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
        usleep(WAIT_TIME);
#endif
        do{
            _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize);
        }while (strstr(serialAns, "X:") == NULL);
        _heap->_arduinoAccess.unlock();
        prepareStringToReceive(serialAns, _heap->_bufsize);
        sscanf(serialAns, "X:%lf Y:%lf Z:%lf E:%lf", &_heap->_currentX, &_heap->_currentY, &_heap->_currentZ, &_heap->_currentE);
        _heap->_isPrintRunning.unlock();
    }
    switch (Axis){
    case 'X':
        return _heap->_currentX;
    case 'Y':
        return _heap->_currentY;
    case 'Z':
        return _heap->_currentZ;
    default:
        return _heap->_currentE;
    }
}

double Repetier::getMax(char Axis)
{
    switch (Axis){
    case 'X':
        return _heap->_maxX;
    case 'Y':
        return _heap->_maxY;
    default:
        return _heap->_maxZ;
    }
}

int Repetier::getNoOfExtruders()
{
    return _heap->_nExtruders;
}

double Repetier::getExtruderTemp(unsigned int extrNo) throw (std::string)
{
    char *seek;
    char format[16];
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize * 2];
    send[0] = '\0';
    serialAns[0] = '\0';
    seek = NULL;
    format[0] = '\0';
    if (extrNo >= _heap->_nExtruders){
        throw std::string("Repetier: Invalid extruder number.");
    }
    if (_heap->_isPrintRunning.try_lock() == true){
        sprintf(send, "M105\n");
        _heap->_arduinoAccess.lock();
        _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
        usleep(WAIT_TIME);
#endif
        do{
            _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize * 2);
        }while (strstr(serialAns, "T:") == NULL);
        _heap->_arduinoAccess.unlock();
        prepareStringToReceive(serialAns, _heap->_bufsize * 2);
        if (_heap->_isCommaDecimalMark == true){
            pointDecimalMarkToComma(serialAns, _heap->_bufsize * 2);
        }
        if (_heap->_nExtruders == 1){
            sscanf(serialAns, "T:%lf ", &_heap->_currentExtrTemp[extrNo]);
        }else{
            sprintf(format, "T%d:", extrNo);
            seek = strstr(serialAns, format);
            if (seek != NULL){
                sprintf(format, "T%d:%%lf", extrNo);
                sscanf(seek, format, &_heap->_currentExtrTemp[extrNo]);
            }
        }
        _heap->_isPrintRunning.unlock();
    }
    return _heap->_currentExtrTemp[extrNo];
}

double Repetier::getBedTemp()
{
    char *seek;
    char send[_heap->_bufsize];
    char serialAns[_heap->_bufsize * 2];
    seek = NULL;
    send[0] = '\0';
    serialAns[0] = '\0';
    if (_heap->_isPrintRunning.try_lock() == true){
        sprintf(send, "M105\n");
        _heap->_arduinoAccess.lock();
        _heap->_arduino->writeStr(send);
#ifdef WAIT_TIME
        usleep(WAIT_TIME);
#endif
        do{
            _heap->_arduino->readUntil(serialAns, '\n', _heap->_bufsize * 2);
        }while (strstr(serialAns, "T:") == NULL);
        prepareStringToReceive(serialAns, _heap->_bufsize * 2);
        if (_heap->_isCommaDecimalMark == true){
            pointDecimalMarkToComma(serialAns, _heap->_bufsize * 2);
        }
        seek = strstr(serialAns, "B:");
        sscanf(seek, "B:%lf ", &_heap->_currentBedTemp);
        _heap->_arduinoAccess.unlock();
        _heap->_isPrintRunning.unlock();
    }
    return _heap->_currentBedTemp;
}

double Repetier::getPrintedFilamentInMeters()
{
    return _heap->_printedFilament;
}

unsigned long Repetier::getTimeOfUsageInSec()
{
    return _heap->_timeOfUsage;
}

bool Repetier::isLogOn()
{
    return _heap->_logout.is_open();
}

bool Repetier::isPrintJobRunning()
{
    if (_heap->_isPrintRunning.try_lock() == true){
        _heap->_isPrintRunning.unlock();
        return false;
    }
    return true;
}

bool Repetier::hasPrinterDisconected()
{
    return _heap->_disconected;
}

void Repetier::turnATXOn()
{
    
}

void Repetier::turnATXOff()
{
    
}