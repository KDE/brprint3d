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
#ifndef PRINTERSETTINGSWIDGET_H
#define PRINTERSETTINGSWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "PrinterSettings.h"
#include "arduinolistener.h"

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
    void setConnectionPorts(QStringList list);


private slots:

    void locateArduino();
    void printLogStatusChanged();
    void on_cb_ExtruderQnt_currentTextChanged(const QString &arg1);

private:
    Ui::PrinterSettingsWidget *ui;
    int extrudersInUse=1;
    arduinoListener *arduino_Listener=nullptr;
    bool garbage=false;
signals:
   void s_extrudersInUse(int n);
   void s_printLogStatus(bool b);
public slots:
   void disableExtrudersQntCb(bool d);
};

#endif // PRINTERSETTINGSWIDGET_H
