//
//  Repetier.cpp
//  KI-C++
//
//  Created by Ayrton Cavalieri de Almeida on 28/06/2015.
//  Copyright (c) 2015 Simple. All rights reserved.
//

#include "Repetier.h"
#include <QDebug>

Repetier::Repetier(int baudrate, std::string serialport, int buffersize, double maxX, double maxY, double maxZ, bool resetWhenConnect, const bool isCommaDecimalMark) throw (std::string){
    char serialAns[buffersize * 2], send[buffersize], *vet;
    unsigned int pos;
    this->isCommaDecimalMark = isCommaDecimalMark;
    printThread = nullptr;
    isPrintingRunning = false;
    terminate = false;
    bufsize = buffersize;
    this->maxX = maxX;
    this->maxY = maxY;
    this->maxZ = maxZ;
    try{
        arduino = new ASerial(serialport, baudrate); //Try to open serial port.
    }catch (std::string exc){
        throw exc;  //If not possible, throw exception.
    }
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "wait") == NULL); //Wait for the Arduino to be ready.
    if(resetWhenConnect == true){ //If user asks to reset Arduino…
        sprintf(send, "M112\n\r"); //Send reset code.
        arduino->writeStr(send);
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize);
        }while(strstr(serialAns, "wait") == NULL); //Wait for the Arduino to be ready.
    }
    sprintf(send, "M115\n\r"); //Asks for printer capabilities string.
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize * 2);
    }while(strstr(serialAns, "FIRMWARE") == NULL); //Waits until answer is received
    vet = strstr(serialAns, "EXTRUDER_COUNT:"); //Searchs for extruder count
    if(vet != NULL){
        pos = strlen("EXTRUDER_COUNT:");
        if(vet[pos] < '0' || vet[pos] > '9'){
            delete arduino;
            std::string exc = "Repetier: Format error when acquiring number of extruders.";
            throw exc;
        }
        switch (vet[pos]){ //Adds extruder number to the object
            case '1':
                this->nExtruders = 1;
                break;
            case '2':
                this->nExtruders = 2;
                break;
            case '3':
                this->nExtruders = 3;
                break;
            case '4':
                this->nExtruders = 4;
                break;
            case '5':
                this->nExtruders = 5;
                break;
            case '6':
                this->nExtruders = 6;
                break;
            default:
                delete arduino;
                std::string exc = "Repetier: This class supports printers with 6 extruders max.";
                throw exc;
        }
    }else{
        delete arduino;
        std::string exc = "Repetier: Could not get the number of extruders.";
        throw exc;
    }
    this->tempExtr = (int*)malloc(this->nExtruders * sizeof(int)); //Initialize the vector with the extruders target temperatures
    if(tempExtr == NULL){
        delete arduino;
        std::string exc = "Repetier: Could not initialize Target Extruder Tempetarute vector.";
        throw exc;
    }
    currentExtrTemp = (double*)malloc(this->nExtruders * sizeof(double)); //Initialize the vector with the extruders temperature
    if(currentExtrTemp == NULL){
        delete arduino;
        free(tempExtr);
        std::string exc = "Repetier: Could not initilize Current Extruder Temperature vector.";
        throw exc;
    }
    sprintf(send, "M105\n\r"); //Ask for current temperatures
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize * 2);
    }while(strstr(serialAns, "T:") == NULL); //Wait for answer…
    if(this->nExtruders == 1){ //Read extruders temperature
        sscanf(serialAns, "T:%lf /%d ", &this->currentExtrTemp[0], &this->tempExtr[0]);
    }else{
        char format[8];
        for(int i = 0; i < this->nExtruders; i++){
            sprintf(format, "T%d:", i);
            vet = strstr(serialAns, format);
            sprintf(format, "T%d:%%lf /%%d ", i);
            sscanf(vet, format, &currentExtrTemp[i], &tempExtr[i]);
        }
    }
    vet = strstr(serialAns, "B:"); //Looks for bed temperature.
    sscanf(vet, "B:%lf /%d ", &currentBedTemp, &tempBed);
    sprintf(send, "M114\n\r"); //Asks for current position
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "X:") == NULL); //Wait for answers…
    prepareStringToReceive(serialAns, this->bufsize);
    sscanf(serialAns, "X:%lf Y:%lf Z:%lf E:%lf", &currentX, &currentY, &currentZ, &currentE); //Set positions…
    this->GCode = NULL;
    this->log = nullptr;
    this->LGCode = nullptr;
    this->logout = nullptr;
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "wait") == NULL); //Wait for Arduino to be idle.
}

Repetier::~Repetier(){
    this->stopPrintJob(); //Stop print job, if thers any
    if(printThread != nullptr){ //If there is an object in printThread pointer…
        printThread->detach();  //Detach the thread…
        delete printThread; //Delete it.
    }
    this->closeFile(); //Close file, if is opened, and save logs, if thers any
    delete this->arduino; //Close serial port.
    free(tempExtr); //Free target temperature vector
    free(currentExtrTemp); //Free current temperature vector
}

void Repetier::saveLogFile(){
    char *printlog;
    while(!this->log->hasFQueueEnded()){ //Runs thru the queue printing in file
        printlog = (char*)this->log->returnInfo();
        (*logout) << printlog << '\n';
    }
    delete this->log;
    delete this->logout;
    this->logout = nullptr;
    this->log = nullptr; //Then closes everything
}

void Repetier::closeFile(){
    if(this->GCode != NULL){ //If GCode is opened…
        delete this->LGCode; //Destroys GCode FQueue
        if(this->logout){
            this->saveLogFile(); //Saves log file, if any…
        }
        fclose(this->GCode); //Closes GCode file
        this->GCode = NULL; //Forget where it was forever.
    }
}

void Repetier::openFile(std::string filepath, bool generateLog) throw (std::string){
    char format[101], *instring, temp[this->bufsize];
    if(this->GCode != NULL){
        this->closeFile(); //If a file was opened, closes it.
    }
    GCode = fopen(filepath.c_str(), "rt"); //Open GCode
    if(GCode == NULL){
        std::string exc = "Repetier: Could not open GCode."; //If could not open GCode…
        throw exc; //…throws exception warning.
    }
    try{
        this->LGCode = new FQueue(100000, 100000); //Create FQueue
    }catch (std::string exc){
        fclose(GCode);
        GCode = NULL;
        throw exc;
    }
    sprintf(format, "%%%d[^\n]\n", bufsize);
    while(fscanf(GCode, format, temp) != EOF){ //Read file until the EOF
        try{
            instring = (char*)malloc((bufsize + 3) * sizeof(char));
            strcpy(instring, temp);
            if(instring[0] != ';'){ //Ignore comentary
                unsigned int p;
                for(p = 0; instring[p] != '\0'; p++){ //Prepare string closing it
                    if(instring[p] == ';'){
                        instring[p] = '\n';
                        instring[p + 1] = '\r';
                        instring[p + 2] = '\0';
                        break;
                    }
                }
                if(instring[p] == '\0'){
                    instring[p] = '\n';
                    instring[p + 1] = '\r';
                    instring[p + 2] = '\0';
                }
            }
            this->LGCode->insertInfo(instring); //Add to Queue
        }catch (std::string exc){
            free(instring);
            delete LGCode;
            LGCode = nullptr;
            fclose(GCode);
            GCode = NULL;
            throw exc;
        }
    }
    try{
        this->LGCode->optimizeFQueue(); //Remove non-used references from FQueue
    }catch (std::string exc){
        delete LGCode;
        LGCode = nullptr;
        fclose(GCode);
        GCode = NULL;
        throw exc;
    }
    if(generateLog == true){ //If users wants log…
        struct tm now;
        long moment = time(NULL);
        localtime_r(&moment, &now); //Asks for current time
        char logname[513];
        sprintf(logname, "printerlog_%dY_%dM_%dD_%dH_%dM_%dS.log", (now.tm_year + 1900), (now.tm_mon + 1),\
                now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
        logout = new std::ofstream(logname); //Creates log with this time
        if(!logout){
            std::string exc = "Repetier: Could not create log file.";
            delete LGCode;
            LGCode = nullptr;
            fclose(GCode);
            GCode = NULL;
            throw exc;
        }
        try{
            this->log = new FQueue((this->LGCode->getFQueueSize() + 1000), 1000); //Creates log FQueue
        }catch (std::string exc){
            delete LGCode;
            LGCode = nullptr;
            fclose(GCode);
            GCode = NULL;
            delete logout;
            logout = nullptr;
            throw exc;
        }
    }
}

bool Repetier::setBedTemp(int temp){
    char send[bufsize], serialAns[bufsize];
    int newBedTemp;
    if(this->tempBed == temp){
        return false;
    }
    sprintf(send, "M140 S%d",temp);
    prepareStringToSend(send, this->bufsize);
    if(isCommaDecimalMark == true){
        commaDecimalMarkToPoint(send, this->bufsize);
    }

    communicationBool.lock();
    arduinoAccess.lock();
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(serialAns[0] != 'T');
    prepareStringToReceive(serialAns, bufsize);
    if(isCommaDecimalMark == true){
        pointDecimalMarkToComma(serialAns, this->bufsize);
    }
    if(sscanf(serialAns, "TargetBed:%d", &newBedTemp) != 0){
        if(newBedTemp == temp){
            this->tempBed = temp;
            if(logout){
                //this->log->insertInfo(logtxt);
                char *logtxt = (char*)malloc(101 * sizeof(char));
                sprintf(logtxt, "Temperature of bed changed to %d oC.", this->tempBed);
                try{
                    this->log->insertInfo(logtxt);
                }catch(std:: string e){
                    throw e;
                }
            }
            arduinoAccess.unlock();
            communicationBool.unlock();
            return true;
        }else{
            if(logout){
                //this->log->insertInfo(logtxt);
                char *logtxt = (char*)malloc(101 * sizeof(char));
                sprintf(logtxt, "Attempted to change bed temperature to %d oC.", temp);
                try{
                    this->log->insertInfo(logtxt);
                }catch(std:: string e){
                    throw e;
                }
            }
            arduinoAccess.unlock();
            communicationBool.unlock();
            return false;
        }
    }
    arduinoAccess.unlock();
    communicationBool.unlock();
    return false;
}

bool Repetier::setExtrTemp(int extrNo, int temp) throw (std::string){
    char serialAns[bufsize], send[bufsize];
    int tempExt;
    if(extrNo < this->nExtruders){
        if(this->tempExtr[extrNo] == temp){
            return false;
        }
        sprintf(send, "M104 S%d T%d", temp, extrNo);
        prepareStringToSend(send, this->bufsize);
        if(isCommaDecimalMark == true){
            commaDecimalMarkToPoint(send, this->bufsize);
        }
        communicationBool.lock();
        arduinoAccess.lock();
        arduino->writeStr(send);
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize);
            //test = strstr(serialAns, "TargetExtr");
        }while(serialAns[0] != 'T');
        prepareStringToReceive(serialAns, this->bufsize);
        if(isCommaDecimalMark == true){
            pointDecimalMarkToComma(serialAns, this->bufsize);
        }
        sprintf(send, "TargetExtr%d:%%d", extrNo);
        if(sscanf(serialAns, send, &tempExt) != 0){
            if(tempExt == temp){
                this->tempExtr[extrNo] = tempExt;
                if(logout){
                    //this->log->insertInfo(logtxt);
                    char *logtxt = (char*)malloc(101 * sizeof(char));
                    sprintf(logtxt, "Extruder temperature %d changed to %d oC.", extrNo, this->tempExtr[extrNo]);
                    try{
                        this->log->insertInfo(logtxt);
                    }catch(std:: string e){
                        throw e;
                    }
                }
                arduinoAccess.unlock();
                communicationBool.unlock();
                return true;
            }else{
                if(logout){
                    //this->log->insertInfo(logtxt);
                    char *logtxt = (char*)malloc(101 * sizeof(char));
                    sprintf(logtxt, "Attempted to change temperature of extruder %d to %d oC.", extrNo, temp);
                    try{
                        this->log->insertInfo(logtxt);
                    }catch(std:: string e){
                        throw e;
                    }
                }
                arduinoAccess.unlock();
                communicationBool.unlock();
                return false;
            }
        }
    }
    arduinoAccess.unlock();
    communicationBool.unlock();
    std::string exc = "Repetier: Invalid extruder number.";
    throw exc;
}

void Repetier::extruderControl(double extrude, double atSpeed){
    char send[this->bufsize], serialAns[this->bufsize];
    sprintf(send, "M82\n\r");
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "ok") == NULL);
    sprintf(send, "G1 E%.4lf F%.2lf\n\r", extrude, atSpeed);
    if(this->isCommaDecimalMark == true){
        commaDecimalMarkToPoint(send, this->bufsize);
    }
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "ok") == NULL);
}

void Repetier::printJob() throw (std::string){
    unsigned long read = 0;
    char *send = NULL, serialAns[bufsize * 2], *logtxt = NULL, currentPos[10], currentTemp[10], *tempTxt;
    sprintf(currentPos, "M114");
    sprintf(currentTemp, "M105");
    prepareStringToSend(currentPos, 9);
    prepareStringToSend(currentTemp, 9);
    communicationBool.lock();
    isPrintingRunning = true;
    communicationBool.unlock();
    while(!this->LGCode->hasFQueueEnded()){
        communicationBool.lock();
        if(terminate == true){
            isPrintingRunning = false;
            communicationBool.unlock();
            return;
        }
        communicationBool.unlock();
        send = (char*)this->LGCode->returnInfo();
        if(send[0] == ';'){
            read++;
            continue;
        }
        arduinoAccess.lock();
        if(read % 200 == 0){
            arduino->writeStr("M117 Job Running\n\r");
            do{
                arduino->readUntil(serialAns, '\n', this->bufsize * 2);
            }while(strstr(serialAns, "ok") == NULL);
        }
        arduino->writeStr(send);
#ifdef WAIT_TIME
        usleep(WAIT_TIME);
#endif
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize * 2);
        }while(strstr(serialAns, "ok") == NULL);
        if(logout){
            restoreSentString(send, bufsize);
            prepareStringToReceive(serialAns, bufsize);
            logtxt = (char*)malloc((50 + bufsize +(2 * bufsize)) * sizeof(char));
            sprintf(logtxt, "GCode SLOC %ld (%s) Ans: %s", (read + 1), send, serialAns);
            try{
                this->log->insertInfo(logtxt);
            }catch (std::string exc){
                throw exc;
            }
        }
        if(read % 5 == 0){
            arduino->writeStr(currentPos);
#ifdef WAIT_TIME
            usleep(WAIT_TIME);
#endif
            do{
                arduino->readUntil(serialAns, '\n', this->bufsize * 2);
            }while(strstr(serialAns, "X:") == NULL);
            if(isCommaDecimalMark == true){
                pointDecimalMarkToComma(serialAns, this->bufsize * 2);
            }
            //prepareStringToReceive(serialAns, this->bufsize * 2);
            sscanf(serialAns, "X:%lf Y:%lf Z:%lf E:%lf\r\n", &currentX, &currentY, &currentZ, &currentE);
            arduino->writeStr(currentTemp);
#ifdef WAIT_TIME
            usleep(WAIT_TIME);
#endif
            do{
                arduino->readUntil(serialAns, '\n', this->bufsize * 2);
            }while(strstr(serialAns, "T:") == NULL);
            prepareStringToReceive(serialAns, this->bufsize * 2);
            if(isCommaDecimalMark == true){
                pointDecimalMarkToComma(serialAns, this->bufsize * 2);
            }
            if(this->nExtruders == 1){
                sscanf(serialAns, "T:%lf ", &this->currentExtrTemp[0]);
                tempTxt = strstr(serialAns, "B:");
                sscanf(tempTxt, "B:%lf ", &this->currentBedTemp);
            }else{
                char format[8];
                tempTxt = strstr(serialAns, "B:");
                sscanf(tempTxt, "B:%lf ", &this->currentBedTemp);
                for(int i = 0; i < this->nExtruders; i++){
                    sprintf(format, "T%d:", i);
                    tempTxt = strstr(serialAns, format);
                    sprintf(format, "T%d:%%lf ", i);
                    sscanf(tempTxt, format, &this->currentExtrTemp[i]);
                }
            }
        }
        read++;
        arduinoAccess.unlock();
    }
    arduinoAccess.lock();
    arduino->writeStr(currentTemp);
#ifdef WAIT_TIME
    usleep(WAIT_TIME);
#endif
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize * 2);
    }while(strstr(serialAns, "T:") == NULL);
    if(isCommaDecimalMark == true){
        pointDecimalMarkToComma(serialAns, this->bufsize * 2);
    }
    arduinoAccess.unlock();
    prepareStringToReceive(serialAns, this->bufsize * 2);
    tempTxt = strstr(serialAns, "B:");
    sscanf(tempTxt, "B:%lf /%d ", &this->currentBedTemp, &this->tempBed);
    if(this->nExtruders == 1){
        sscanf(serialAns, "T:%lf /%d ", &this->currentExtrTemp[0], &this->tempExtr[0]);
    }else{
        char format[16];
        for(int i = 0; i < this->nExtruders; i++){
            sprintf(format, "T%d:", i);
            tempTxt = strstr(serialAns, format);
            sprintf(format, "T%d:%%lf /%%d ", i);
            sscanf(serialAns, format, &this->currentExtrTemp[i], &this->tempExtr[i]);
        }
    }
    communicationBool.lock();
    isPrintingRunning = false;
    communicationBool.unlock();
}

void Repetier::startPrintJob(bool fromBegining){
    if(fromBegining == true){
        this->LGCode->resetFQueue();
    }
    this->stopPrintJob();
    if(printThread != nullptr){
        printThread->detach();
        delete printThread;
    }
    terminate = false;
    printThread = new std::thread(&Repetier::printJob, this);
}

void Repetier::stopPrintJob(){
    if(isPrintingRunning == true){
        communicationBool.lock();
        terminate = true;
        communicationBool.unlock();
        while(isPrintingRunning != false){
            usleep(10000);
        }
        printThread->detach();
        delete printThread;
        printThread = nullptr;
    }
}

void Repetier::scramPrinter() throw (std::string){
    char send[bufsize], serialAns[bufsize];
    int cont = 0;
    this->stopPrintJob();
    arduinoAccess.lock();
    sprintf(send, "M112\n\r");
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\r', this->bufsize);
        cont++;
    }while(strstr(serialAns, "wait") == NULL && cont < 5);
    if(cont == 5){
        std::string exc = "Repetier: Could not comunicate with Arduino.";
        arduinoAccess.unlock();
        throw exc;
    }
    arduinoAccess.unlock();
}

void Repetier::homeAxis(char Axis) throw (std::string){
    char send[this->bufsize], serialAns[this->bufsize];
    if(Axis >= 'a' && Axis <= 'z'){
        Axis-='a';
        Axis+='A';
    }
    if(Axis != 'X' && Axis != 'Y' && Axis != 'Z'){
        std::string exc = "Repetier: Invalid Axis.";
        throw exc;
    }
    sprintf(send, "G28 %c0\n\r", Axis);
    arduinoAccess.lock();
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "X:") == NULL);
    switch (Axis) {
        case 'X':
            this->currentX = 0.0;
            break;
        case 'Y':
            this->currentY = 0.0;
            break;
        case 'Z':
            this->currentZ = 0.0;
            break;
        default:
            break;
    }
    arduinoAccess.unlock();
}

void Repetier::homeAllAxis(){
    char send[bufsize], serialAns[bufsize];
    sprintf(send, "G28\n\r");
    arduinoAccess.lock();
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "X:") == NULL);
    currentX = currentY = currentZ = 0.0;
    arduinoAccess.unlock();
}

void Repetier::moveAxisToPos(char axis, double pos) throw (std::string){
    char send[this->bufsize], serialAns[this->bufsize], *test;
    if(axis >= 'a' && axis <= 'z'){
        axis-='a';
        axis+='A';
    }
    if(axis != 'X' && axis != 'Y' && axis != 'Z'){
        std::string exc = "Repetier: Invalid axis.";
        throw exc;
    }
    sprintf(send, "G1 %c%.3lf", axis, pos);
    prepareStringToSend(send, this->bufsize);
    if(isCommaDecimalMark == true){
        commaDecimalMarkToPoint(send, this->bufsize);
    }
    arduinoAccess.lock();
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while(strstr(serialAns, "ok") == NULL);
    sprintf(send, "M114");
    prepareStringToSend(send, this->bufsize);
    arduino->writeStr(send);
    do{
        arduino->readUntil(serialAns, '\n', this->bufsize);
    }while (strstr(serialAns, "X:") == NULL);
    arduinoAccess.unlock();
    if(isCommaDecimalMark == true){
        pointDecimalMarkToComma(serialAns, this->bufsize);
    }
    switch (axis) {
        case 'X':
            sscanf(serialAns, "X:%lf ", &this->currentX);
            break;
        case 'Y':
            test = strstr(serialAns, "Y:");
            sscanf(test, "Y:%lf ", &this->currentY);
            break;
        case 'Z':
            test = strstr(serialAns, "Z:");
            sscanf(test, "Z:%lf ", &this->currentZ);
            break;
        default:
            break;
    }
}

double Repetier::getCurrentE(){
    return currentE;
}

double Repetier::getCurrentXPos(){
    char send[this->bufsize], serialAns[this->bufsize];
    if(this->isPrintingRunning == false){
        sprintf(send, "M114\n\r");
        //sscanf(serialAns, "X:%lf Y:%lf Z:%lf E:%lf\r\n", &currentX, &currentY, &currentZ, &currentE);
        arduinoAccess.lock();
        arduino->writeStr(send);
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize);
        }while(strstr(serialAns, "X:") == NULL);
        sscanf(serialAns, "X:%lf ", &currentX);
        arduinoAccess.unlock();
    }
    return currentX;
}

double Repetier::getCurrentYPos(){
    char send[this->bufsize], serialAns[this->bufsize], *p;
    if(this->isPrintingRunning == false){
        sprintf(send, "M114\n\r");
        arduinoAccess.lock();
        arduino->writeStr(send);
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize);
            p = strstr(serialAns, "Y:");
        }while(p == NULL);
        sscanf(p, "Y:%lf ", &currentY);
        arduinoAccess.unlock();
    }
    return currentY;
}

double Repetier::getCurrentZPos(){
    char send[this->bufsize], serialAns[this->bufsize], *p;
    if(this->isPrintingRunning == false){
        sprintf(send, "M114\n\r");
        arduinoAccess.lock();
        arduino->writeStr(send);
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize);
            p = strstr(serialAns, "Z:");
        }while(p == NULL);
        sscanf(p, "Z:%lf ", &currentY);
        arduinoAccess.unlock();
    }
    return currentZ;
}

double Repetier::getMaxX(){
    return maxX;
}

double Repetier::getMaxY(){
    return maxY;
}

double Repetier::getMaxZ(){
    return maxZ;
}

int Repetier::getNoOfExtruders(){
    return this->nExtruders;
}

double Repetier::getExtruderTemp(unsigned int extrNo) throw (std::string){
    char send[this->bufsize], serialAns[this->bufsize * 2], *tempTxt = NULL, format[8];
    if(extrNo >= this->nExtruders){
        std::string exc = "Repetier: Invalid extruder number.";
        throw exc;
    }
    if(this->isPrintingRunning == false){
        sprintf(send, "M105\n\r");
        arduinoAccess.lock();
        arduino->writeStr(send);
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize * 2);
        }while(strstr(serialAns, "T:") == NULL);
        if(isCommaDecimalMark == true){
            pointDecimalMarkToComma(serialAns, this->bufsize  * 2);
        }
        prepareStringToReceive(serialAns, this->bufsize);
        if(this->nExtruders == 1){
            sscanf(serialAns, "T:%lf ", &this->currentExtrTemp[extrNo]);
        }else{
            sprintf(format, "T%d:", extrNo);
            tempTxt = strstr(serialAns, format);
            sprintf(format, "T%d:%%lf ", extrNo);
            sscanf(tempTxt, format, &this->currentExtrTemp[extrNo]);
        }
        arduinoAccess.unlock();
    }
    return this->currentExtrTemp[extrNo];
}

double* Repetier::getAllExtrudersTemp() throw (std::string){
    double *vet;
    vet = (double*)malloc(this->nExtruders * sizeof(double));
    for(unsigned int i = 0; i < this->nExtruders; i++){
        this->getExtruderTemp(i);
    }
    return vet;
}

double Repetier::getBedTemp(){
    char send[this->bufsize], serialAns[this->bufsize * 2], *read;
    if(this->isPrintingRunning == false){
        sprintf(send, "M105\n\r");
        arduinoAccess.lock();
        arduino->writeStr(send);
        do{
            arduino->readUntil(serialAns, '\n', this->bufsize * 2);
        }while(strstr(serialAns, "T:") == NULL);
        if(isCommaDecimalMark == true){
            pointDecimalMarkToComma(serialAns, this->bufsize * 2);
        }
        read = strstr(serialAns, "B:");
        sscanf(read, "B:%lf ", &this->currentBedTemp);
        arduinoAccess.unlock();
    }
   // qDebug() << double(this->currentBedTemp);
    return this->currentBedTemp;
}

bool Repetier::isLogOn(){
    return logout != nullptr ? true : false;
}

bool Repetier::isPrintJobRunning(){
    return this->isPrintingRunning;
}
