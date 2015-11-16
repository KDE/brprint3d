/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 (c) 2015 BRPrint3D Authors

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

/*
 * This thread updates on the screend the values of temperatures of the printer and position of the extrudern while the printer is connect.
 */
#include "threadRotine.h"
#include <QDebug>

ThreadRoutine::ThreadRoutine(Repetier *printer, int *extrudersInUse)
{
    this->printer = printer;
    this->stopLoop = false;
    this->isPrintJobRunning = true;
    this->extrudersInUse = extrudersInUse;
}


void ThreadRoutine::run()
{
    while (true) {
        for (int i = 0; i < (*extrudersInUse); i++) {
            this->extrudersTemp[i] = this->printer->getExtruderTemp(i);
        }

        this->posX = this->printer->getCurrentXPos();
        this->posY = this->printer->getCurrentYPos();
        this->posZ = this->printer->getCurrentZPos();
        sleep(2);
        emit updateTemp(extrudersTemp, printer->getBedTemp());
        emit updatePos(this->posX, this->posY, this->posZ);
        this->isPrintJobRunning = this->printer->isPrintJobRunning();
        if (this->isPrintJobRunning == false)
            emit finishedJob(true);
        if (stopLoop == true)
            break;
    }
}

void ThreadRoutine::setLoop(bool b)
{
    this->stopLoop = b;
}

ThreadRoutine::~ThreadRoutine()
{
    this->deleteLater();
}

