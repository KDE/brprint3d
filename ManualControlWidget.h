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
#ifndef MANUALCONTROLWIDGET_H
#define MANUALCONTROLWIDGET_H
#include "ExtruderControlWidget.h"
#include <QWidget>
#include "KI/Repetier.h"
#include "threadRotine.h"
#include "PrinterSettings.h"
#include <QTabWidget>
#include <QSettings>
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <stdio.h>
namespace Ui {
class ManualControlWidget;
}

class ManualControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManualControlWidget(QWidget *parent = 0);
    ~ManualControlWidget();
    void init();
    void setGcodePreview(QString t);
    void startThreadRoutine();
    void stopThreadRoutine();
    void setBedStatus(bool b);
    void setExtruderStatus(bool b);
    void getPrinterObject(Repetier *printer_object);
    void setInitialMarks();
    void constructPrinterObject(PrinterSettings pSettings);
    void destructPrinterObject();
    void hideExtruders(int e);
    void startPrintJob(QString filePath);
    ThreadRoutine *temp=nullptr;

private:
    Ui::ManualControlWidget *ui;
    Repetier *printerObject=nullptr;
    int extrudersInUse=1;
    QString pathslicer,pathcura;
    void locateSlicer();
    void locateCura();
    QSettings settings;
    bool garbage,playStatus,printLogStatus,pauseStatus=false;
    int extruderQnt;
signals:
    void checkConnectButton(bool b);
    void enablePlayButton(bool b);
    void disableCbExtruderQnt(bool b);
    void disablePositionButtons(bool b);
private slots:
    void updateTemp(double *tempExtruders,double tempBed);
    void startBed(bool checked);
    void startExtruders(bool checked);
    void disableExtrudersButtons(bool checked);
    void setNewBedTemp();
    void setNewExtruderTemp();
    void setPlayStatus(bool b);
    void isPrintJobRunning(bool b);
    void spinEditFinished();
    void setValue(int v);

public slots:
    void setExtrudersInUse(int e);
    void setPrintLogStatus(bool b);
    void pausePrintJob(bool b);
    void stopPrintJob();
    void stopOnEmergency();
   
};

#endif // MANUALCONTROLWIDGET_H
