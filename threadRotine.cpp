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
     printer = printer;
     stopLoop = false;
     isPrintJobRunning = true;
     extrudersInUse = extrudersInUse;
}


void ThreadRoutine::run()
{
    while (true) {
        for (int i = 0; i < (*extrudersInUse); i++) {
             extrudersTemp[i] =  printer->getExtruderTemp(i);
        }

         posX =  printer->getCurrentXPos();
         posY =  printer->getCurrentYPos();
         posZ =  printer->getCurrentZPos();
        sleep(2);
        emit updateTemp(extrudersTemp, printer->getBedTemp());
        emit updatePos( posX,  posY,  posZ);
         isPrintJobRunning =  printer->isPrintJobRunning();
        if ( isPrintJobRunning == false)
            emit finishedJob(true);
        if (stopLoop == true)
            break;
    }
}

void ThreadRoutine::setLoop(bool b)
{
     stopLoop = b;
}

ThreadRoutine::~ThreadRoutine()
{
     deleteLater();
}

