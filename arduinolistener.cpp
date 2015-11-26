/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

Copyright (C) 2015 BRPrint3D Authors

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/

#include "arduinolistener.h"

arduinoListener::arduinoListener()
{
    test = false;
}

void arduinoListener::run()
{
    while (true) {
        garbage = std::system("lsusb > arduinoListener.txt");
        QFile arduino("arduinoListener.txt");
        if (arduino.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&arduino);
            QString file = in.readAll();
            arduino.close();
            if ((test = file.contains("Arduino")) == true) {
                emit arduinoConnect();
                break;
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

