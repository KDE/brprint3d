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
    Repetier *printer;
    QMutex mutexIno;
    bool stopLoop;
    double posX, posY,posZ;
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
    void updateExt(double posX, double posY, double posZ);
    void finishedJob(bool b);
};

#endif // THREADROUTINE_H
