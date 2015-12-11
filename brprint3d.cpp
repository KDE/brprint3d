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

#include "brprint3d.h"
#include "ui_Pandora.h"

BrPrint3D::BrPrint3D(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::BrPrint3D), 
    bt_import(new BigButton(this,tr("Import GCode"),":/Icons/Icons/import.png", false)),
    bt_open(new BigButton(this,tr("Open File"),":/Icons/Icons/openFile.png", false)),
    bt_connect(new BigButton(this,tr("Connect"),":/Icons/Icons/connect.png", true)),
    bt_play(new BigButton(this,tr("Play"),":/Icons/Icons/play.png", true)),
    bt_pause(new BigButton(this,tr("Pause"),":/Icons/Icons/pause.png", true)),
    bt_stop(new BigButton(this,tr("Stop"),":/Icons/Icons/stop.png", false)),
    bt_stopOnEmergency(new BigButton(this,tr("Emergency Stop"),":/Icons/Icons/emergency.png", false)),
    vtkView(new vtkWidget())
{
    ui->setupUi(this);
    
    ui->ly_ConteinerLeft->addWidget(bt_import);
    ui->ly_ConteinerLeft->addWidget(bt_open);
    ui->ly_ConteinerLeft->addWidget(bt_connect);

    ui->ly_ConteinerRight->addWidget(bt_play);
    ui->ly_ConteinerRight->addWidget(bt_pause);
    ui->ly_ConteinerRight->addWidget(bt_stop);
    ui->ly_ConteinerRight->addWidget(bt_stopOnEmergency);

    ui->_vtkConteiner->addWidget(vtkView);

    connect(ui->_PrinterSettings,&PrinterSettingsWidget::s_extrudersInUse,ui->_ManualControl,&ManualControlWidget::setExtrudersInUse);
    connect(bt_import,&BigButton::clicked,this,&BrPrint3D::openFile);
    connect(bt_open,&BigButton::clicked,this,&BrPrint3D::openFile);
    connect(bt_connect,&BigButton::clicked,this,&BrPrint3D::connectPrinter);
    connect(bt_connect,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(ui->_PrinterSettings,&PrinterSettingsWidget::s_printLogStatus,ui->_ManualControl,&ManualControlWidget::setPrintLogStatus);
    connect(bt_play,&BigButton::clicked,this,&BrPrint3D::startPrintJob);
    connect(bt_play,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(bt_play,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::setPlayStatus);
    connect(ui->_ManualControl,&ManualControlWidget::disableCbExtruderQnt,ui->_PrinterSettings,&PrinterSettingsWidget::disableExtrudersQntCb);
    connect(bt_pause,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::pausePrintJob);
    connect(bt_pause,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(bt_stop,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::stopPrintJob);
    connect(bt_stop,&BigButton::clicked,this,&BrPrint3D::stopPrintJob);
    connect(bt_stop,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(bt_stopOnEmergency,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::stopOnEmergency);
    connect(ui->bt_hide,&QPushButton::clicked,this,&BrPrint3D::hidePrinterSettings);
    connect(ui->_ManualControl,&ManualControlWidget::checkConnectButton,bt_connect,&BigButton::setChecked);
    connect(ui->_PrinterSettings,&PrinterSettingsWidget::updateCube,vtkView,&vtkWidget::updateCube);
    connect(vtkView,&vtkWidget::layersCount,ui->_ManualControl,&ManualControlWidget::setLayersCount);
    connect(this,&BrPrint3D::callFilCount,ui->_ManualControl,&ManualControlWidget::setFilCount);

    connect(vtkView,&vtkWidget::layersCount,ui->_ManualControl,&ManualControlWidget::setLayersCount);

}

BrPrint3D::~BrPrint3D()
{
    delete ui;
}
void BrPrint3D::init()
{
    ui->_PrinterSettings->hide();
    ui->_PrinterSettings->init();
    ui->_ManualControl->init();
    setEnabled(false);
}

void BrPrint3D::setEnabled(bool b)
{
    bt_play->setEnabled(b);
    bt_pause->setEnabled(b);
    bt_stop->setEnabled(b);
    bt_stopOnEmergency->setEnabled(b);
}

void BrPrint3D::openFile()
{
    QString typeGcode("*.gcode");
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
                emit callFilCount(filePath);
                ui->_ManualControl->setGcodePreview(text);
                if (bt_connect->isChecked())
                    bt_play->setEnabled(true);

            }
        }

    else if(QFileInfo(filePath).completeSuffix()=="STL" ||QFileInfo(filePath).completeSuffix()=="stl"){
        vtkView->renderSTL(filePath);
    }
}

void BrPrint3D::connectPrinter(bool checked)
{
    if (checked) {
        psettings = ui->_PrinterSettings->getCurrentSettings();
        ui->_ManualControl->constructPrinterObject(psettings);
        setEnabled(true);
        bt_pause->setEnabled(false);
        bt_stop->setEnabled(false);
    } else {
        ui->_ManualControl->destructPrinterObject();
    }
}

void BrPrint3D::startPrintJob(bool checked)
{
    if (checked) {
        ui->_ManualControl->startPrintJob(filePath);
        bt_play->setEnabled(false);
        bt_pause->setEnabled(true);
        bt_stop->setEnabled(true);
    }
}
void BrPrint3D::stopPrintJob()
{
    bt_play->setEnabled(true);
    bt_play->setChecked(false);
    bt_play->setIcon(QIcon(":/Icons/Icons/play.png"));
    bt_pause->setEnabled(false);
    bt_stop->setEnabled(false);
}

void BrPrint3D::hidePrinterSettings()
{
    if(ui->bt_hide->isChecked()) {
        ui->_PrinterSettings->show();
        ui->bt_hide->setText(tr("Settings - Hide"));
    } else {    ui->_PrinterSettings->hide();
        ui->bt_hide->setText(tr("Settings - Show"));
    }
}

void BrPrint3D::changeIcon(bool checked)
{
    //TODO: Remove this method - Icon handling should be on the BigButton class, not here.
    // Since you are using 'onClick' to mark if a widget is checked, consider using a QToolButton
    // instead of a QPush button and let the button manage the OnClicked / OnChecked automatically.
    if( sender() == bt_play ) {
        if (checked){
            // use btn_play->setEnabled();
            QIcon icon(":/Icons/Icons/playOnClick.png");
            QPixmap pix(":/Icons/Icons/playOnClick.png");
            icon.addPixmap(pix,QIcon::Disabled,QIcon::Off);
            bt_play->setIcon(icon);
        } else {
            bt_play->setIcon(QIcon(":/Icons/Icons/play.png"));
            bt_play->setChecked(false);
        }
    } else if (sender()==bt_pause) {
        if (checked) {
            bt_pause->setIcon(QIcon(":/Icons/Icons/pauseOnClick.png"));
        } else {
            bt_pause->setIcon(QIcon(":/Icons/Icons/pause.png"));
        }
    } else if (sender()==bt_connect) {
        if (checked) {
            bt_connect->setIcon(QIcon(":/Icons/Icons/connectOnClick.png"));
        } else {
            bt_connect->setIcon(QIcon(":/Icons/Icons/connect.png"));
        }
    }
}

/*void BrPrint3D::resetPlayButton(){
    bt_play->setChecked(false);
    bt_play->setIcon(QIcon(":/Icons/Icons/play.png"));

}*/
