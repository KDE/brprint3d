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

#include "brprint3d.h"
#include "ui_Pandora.h"

BrPrint3D::BrPrint3D(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::BrPrint3D)
{
    ui->setupUi(this);
    bt_import = new BigButton(0,"Import \nGCode");
    bt_open = new BigButton(0,"Open File");
    bt_connect = new BigButton(0,"Connect",true);

    ui->ly_ConteinerLeft->addWidget(bt_import);
    ui->ly_ConteinerLeft->addWidget(bt_open);
    ui->ly_ConteinerLeft->addWidget(bt_connect);

    bt_play = new BigButton(0,"Play",true);
    bt_pause = new BigButton(0,"Pause",true);
    bt_stop = new BigButton(0,"Stop",true);
    bt_stopOnEmergency = new BigButton(0,"Emergency \nStop");

    ui->ly_ConteinerRight->addWidget(bt_play);
    ui->ly_ConteinerRight->addWidget(bt_pause);
    ui->ly_ConteinerRight->addWidget(bt_stop);
    ui->ly_ConteinerRight->addWidget(bt_stopOnEmergency);

    vtkView = new vtkWidget();
    ui->_vtkConteiner->addWidget(vtkView);

    connect(ui->_PrinterSettings,&PrinterSettingsWidget::s_extrudersInUse,ui->_ManualControl,&ManualControlWidget::setExtrudersInUse);
    connect(bt_import,&BigButton::clicked,this,&BrPrint3D::openFile);
    connect(bt_open,&BigButton::clicked,this,&BrPrint3D::openFile);
    connect(bt_connect,&BigButton::clicked,this,&BrPrint3D::connectPrinter);
    connect(ui->_PrinterSettings,&PrinterSettingsWidget::s_printLogStatus,ui->_ManualControl,&ManualControlWidget::setPrintLogStatus);
    connect(bt_play,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::startPrintJob);
    connect(ui->_ManualControl,&ManualControlWidget::disableCbExtruderQnt,ui->_PrinterSettings,&PrinterSettingsWidget::disableExtrudersQntCb);
    connect(bt_pause,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::pausePrintJob);
    connect(bt_stop,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::stopPrintJob);
    connect(bt_stop,&BigButton::clicked,this,&BrPrint3D::stopPrintJob);


}

BrPrint3D::~BrPrint3D()
{
    delete ui;
}
void BrPrint3D::init()
{


}
void BrPrint3D::openFile()
{   QString typeGcode("*.gcode");
    QString typeAll("*.gcode *.stl *.STL");
    if(sender()==bt_import){
        filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), typeGcode);
    }
    if(sender()==bt_open){
        filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), typeAll);
    }
        if (!filePath.isEmpty() && QFileInfo(filePath).completeSuffix() == "gcode") {
            QFile gcode(filePath);
            if (gcode.open(QFile::ReadOnly | QFile::Text)) {
                QTextStream in(&gcode);
                QString text = in.readAll();
                vtkView->renderGcode(text);
                gcode.close();
                ui->_ManualControl->setGcodePreview(text);
                if (bt_connect->getCheckedStatus())
                    bt_play->setEnabled(true);

            }
        }
        else if(QFileInfo(filePath).completeSuffix()=="STL" ||QFileInfo(filePath).completeSuffix()=="stl"){
                 vtkView->renderSTL(filePath);
             }
}

void BrPrint3D::connectPrinter(){
    psettings = ui->_PrinterSettings->getCurrentSettings();
    ui->_ManualControl->constructPrinterObject(psettings);
}

void BrPrint3D::startPrintJob(){
    ui->_ManualControl->startPrintJob(filePath);
    bt_play->setEnabled(false);
    bt_pause->setEnabled(true);
    bt_stop->setEnabled(true);
}
void BrPrint3D::stopPrintJob(){
    bt_play->setEnabled(true);
    bt_pause->setEnabled(false);
    bt_stop->setEnabled(false);
}

