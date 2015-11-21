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

#ifndef THREADROUTINE_H
#define THREADROUTINE_H
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QReadWriteLock>
#include "KI/Repetier.h"

class ThreadRoutine : public QThread
{
    Q_OBJECT

private:
    Repetier *printer=nullptr;
    QMutex mutexIno;
    bool stopLoop;
    double posX, posY, posZ;
    bool isPrintJobRunning;
    double extrudersTemp[4];
    int *extrudersInUse;



public:
    ThreadRoutine(Repetier *printer, int *extrudersInUse);
    ~ThreadRoutine();
    virtual void run() Q_DECL_OVERRIDE;
    void setLoop(bool b);

signals:
    void updateTemp(double *extrudersTemp, double tempBed);
    void updatePos(double posX, double posY, double posZ);
    void finishedJob(bool b);
};

#endif // THREADROUTINE_H
