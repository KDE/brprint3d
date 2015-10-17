/*
 * This file starts a thread that run while the arduino is not connect or find
 *
 *
*/
#include "arduinolistener.h"

arduinoListener::arduinoListener()
{
    this->test = false;
}

void arduinoListener::run()
{
    while(true)
        {
            garbage=std::system("lsusb > arduinoListener.txt");
            QFile arduino("arduinoListener.txt");
            QString word;
            if(arduino.open(QIODevice::ReadOnly|QIODevice::Text))
            {       QTextStream in(&arduino);
                    QString file = in.readAll();
                    arduino.close();
                    if((test=file.contains("Arduino"))==true)
                    {    word = "Arduino";
                         emit arduinoConnect(true, word);
                    }
                    else if((test=file.contains("QinHeng"))==true)
                    {   word = "ch341-uart";
                        emit arduinoConnect(true,word);
                    }
                    else
                        usleep(5000);
            }
        }

}

arduinoListener::~arduinoListener()
{
    this->deleteLater();
}

