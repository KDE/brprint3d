
/*
 The MIT License (MIT)
 
 Copyright (c) 2014 Tod E. Kurt
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef __KI_C____Arduino_Serial__
#define __KI_C____Arduino_Serial__

#include <stdint.h>   // Standard types
#include <stdio.h>    // Standard input/output definitions
#include <unistd.h>   // UNIX standard function definitions
#include <fcntl.h>    // File control definitions
#include <errno.h>    // Error number definitions
#include <termios.h>  // POSIX terminal control definitions
#include <string.h>   // String function definitions
#include <sys/ioctl.h>
#include <iostream>

class ASerial{
private:
    std::string serialport;
    int fd, baudrate, error;
    struct termios toptions;
public:
    ASerial(std::string serialport, int baudrate) throw (std::string);
    ~ASerial();
    std::string getSerialPort();
    int getBaudrate();
    int getError();
    int closePort();
    int resetSerialPort();
    int writeStr(const char *str);
    int writeByte(uint8_t byte);
    int readUntil(char *buf, char until, int buf_max);
    int readNBytes(char *buf, int buf_max);
    int flush();
};

#endif /* defined(__KI_C____Arduino_Serial__) */
