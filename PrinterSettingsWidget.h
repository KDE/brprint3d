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
#ifndef PRINTERSETTINGSWIDGET_H
#define PRINTERSETTINGSWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "PrinterSettings.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>
#include <QInputDialog>


namespace Ui {
class PrinterSettingsWidget;
}

class PrinterSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterSettingsWidget(QWidget *parent = 0);
    ~PrinterSettingsWidget();
    void init();
    PrinterSettings getCurrentSettings();



private slots:

    void locateArduino();
    void printLogStatusChanged();
    void on_cb_ExtruderQnt_currentTextChanged(const QString &arg1);
    void sendValue();

private:
    Ui::PrinterSettingsWidget *ui;
    int extrudersInUse=1;
    bool garbage=false;
    QTimer timer;
    QStringList actPortList;
    QStringList antPortList;
    QSettings settings;
    PrinterSettings pSettings;

    void setSettings(PrinterSettings p);
    PrinterSettings loadSettings(QString q);
    void saveSettings();
signals:
   void s_extrudersInUse(int n);
   void s_printLogStatus(bool b);
   void updateCube(int v, QChar axis);

public slots:
   void disableExtrudersQntCb(bool d);
};

#endif // PRINTERSETTINGSWIDGET_H
