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
    while(true)
    {
        for(int i=0;i<(*extrudersInUse);i++)
        {
            this->extrudersTemp[i]=this->printer->getExtruderTemp(i);
        }

        this->posX = this->printer->getCurrentXPos();
        this->posY = this->printer->getCurrentYPos();
        this->posZ = this->printer->getCurrentZPos();
        sleep(2);
        emit updateTemp(extrudersTemp,printer->getBedTemp());
        emit updateExt(this->posX,this->posY,this->posZ);
        this->isPrintJobRunning = this->printer->isPrintJobRunning();
        if(this->isPrintJobRunning==false)
            emit finishedJob(true);
       if(stopLoop==true)
                break;
    }
}

void ThreadRoutine::setLoop(bool b)
{
    this->stopLoop = b;
}

ThreadRoutine::~ThreadRoutine(){
    this->deleteLater();
}

