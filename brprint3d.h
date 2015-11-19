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

#ifndef BRPRINT3D_H
#define BRPRINT3D_H
#include <QMainWindow>
#include <Windows/loading.h>
#include <Windows/documentation.h>
#include <Windows/aboutbrprint.h>
#include <Windows/help.h>
#include <Windows/legalwarning.h>
#include <Windows/loading.h>
#include "KI/Repetier.h"
#include "threadRotine.h"
#include "vtkWidget.h"
#include "PrinterSettings.h"
#include "BigButton.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <QTranslator>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QVariant>
#include <QSettings>
#include <QObject>
#include <QList>
#include <QInputDialog>
#include <QList>
#include <QStandardPaths>

namespace Ui
{
class BrPrint3D;
}

class BrPrint3D : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrPrint3D(QWidget *parent = 0);
    ~BrPrint3D();
    void init();
    BigButton *bt_import;
    BigButton *bt_open;
    BigButton *bt_connect;
    BigButton *bt_play;
    BigButton *bt_pause;
    BigButton *bt_stop;
    BigButton *bt_stopOnEmergency;
private:
    Ui::BrPrint3D *ui;
    vtkWidget *vtkView;
    PrinterSettings psettings;
    QString filePath;


private slots:
    void openFile();
    void connectPrinter(bool checked);
    void startPrintJob(bool checked);
    void stopPrintJob();
    void hidePrinterSettings();
signals:
    void s_playStatus(bool b);
    void s_pauseStatus(bool b);

};

#endif // BRPRINT3D_H
