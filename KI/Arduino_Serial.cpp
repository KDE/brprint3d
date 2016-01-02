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

#include "Arduino_Serial.h"

ASerial::ASerial(std::string serialport, int baudrate) throw (std::string)
{
    _serialport = serialport;
    _baudrate = baudrate;
    _fd = open(this->_serialport.c_str(), O_RDWR | O_NONBLOCK);
    if (this->_fd == -1){
        throw std::string("ASerial: Could not open serialport: " + _serialport + '.');
    }
    if (tcgetattr(_fd, &_toptions) < 0){
        throw std::string("ASerial: Could not get term attributes.");
    }
    speed_t brate = this->_baudrate; // let you override switch below if needed
    switch (_baudrate){
    case 4800:
        brate = B4800;
        break;
    case 9600:
        brate = B9600;
        break;
#ifdef B14400
    case 14400:
        brate = B14400;
        break;
#endif
    case 19200:
        brate = B19200;
        break;
#ifdef B28800
    case 28800:
        brate = B28800;
        break;
#endif
    case 38400:
        brate = B38400;
        break;
    case 57600:
        brate = B57600;
        break;
    case 115200:
        brate = B115200;
        break;
#ifdef B230400
    case 230400:
        brate = B230400;
        break;
#endif
    }
    cfsetispeed(&_toptions, brate);
    cfsetospeed(&_toptions, brate);
    // 8N1
    _toptions.c_cflag &= ~PARENB;
    _toptions.c_cflag &= ~CSTOPB;
    _toptions.c_cflag &= ~CSIZE;
    _toptions.c_cflag |= CS8;
    // no flow control
    _toptions.c_cflag &= ~CRTSCTS;
    _toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    _toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

    _toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    _toptions.c_oflag &= ~OPOST; // make raw
    _toptions.c_cc[VMIN]  = 0;
    _toptions.c_cc[VTIME] = 0;
    tcsetattr(_fd, TCSANOW, &_toptions);
    if (tcsetattr(_fd, TCSAFLUSH, &_toptions) < 0) {
        throw std::string("ASerial: Couldn't set term attributes.");
    }
}

ASerial::~ASerial()
{
    close(_fd);
}

std::string ASerial::getSerialPort()
{
    return _serialport;
}

int ASerial::getBaudrate()
{
    return _baudrate;
}

int ASerial::closePort()
{
    return close(_fd);
}

int ASerial::resetSerialPort()
{
    close(_fd);
    _fd = open(_serialport.c_str(), O_RDWR | O_NONBLOCK);
    if (_fd == -1)
        return -1;
    tcsetattr(_fd, TCSANOW, &_toptions);
    if (tcsetattr(_fd, TCSAFLUSH, &_toptions) < 0) {
        return -3;
    }
    return 0;
}

int ASerial::writeStr(const char *str)
{
    int len = (int)strlen(str);
    int n = (int)write(_fd, str, len);
    if (n != len) {
        return -1;
    }
    return 0;
}

int ASerial::writeByte(uint8_t byte)
{
    int n = (int)write(_fd, &byte, 1);
    if (n != 1)
        return -1;
    return 0;
}

int ASerial::readUntil(char *buf, char until, int buf_max)
{
    char b[2];  // read expects an array, so we give it a 2-byte array
    int i = 0;
    int n;
    b[1] = '\0';
    do{
        n = (int)read(_fd, b, 1);  // read a char at a time
        /*if (n == -1)
            return -1;    // couldn't read
        if (n == 0) {
            continue;
        }
        buf[i] = b[0];*/
        switch (n){
        case 0:
            continue;
        case -1:
            return -1;
        default:
            buf[i] = b[0];
        }
        i++;
    }while (b[0] != until && i < buf_max);

    buf[i] = 0;  // null terminate the string*/
    return 0;
}

int ASerial::readNBytes(char *buf, int buf_max)
{
    char b[2];
    int i;
    int n;
    b[1] = '\0';
    for (i = 0; i < buf_max; i++) {
        n = (int)read(_fd, b, 1);
        switch (n) {
        case 0:
            continue;
        case -1:
            return -1;
        default:
            buf[i] = b[0];
            break;
        }
    }
    buf[i] = '\0';
    return 0;
}

int ASerial::flush()
{
    usleep(1); //required to make flush work, for some reason
    return tcflush(_fd, TCIOFLUSH);
}
