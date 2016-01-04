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
    ui(new Ui::BrPrint3D)
{
    ui->setupUi(this);

    connect(ui->_PrinterSettings,&PrinterSettingsWidget::s_extrudersInUse,ui->_ManualControl,&ManualControlWidget::setExtrudersInUse);
    connect(ui->bt_open,&BigButton::clicked,this,&BrPrint3D::openFile);
    connect(ui->bt_connect,&BigButton::clicked,this,&BrPrint3D::connectPrinter);
    connect(ui->bt_connect,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(ui->_PrinterSettings,&PrinterSettingsWidget::s_printLogStatus,ui->_ManualControl,&ManualControlWidget::setPrintLogStatus);
    connect(ui->bt_play,&BigButton::clicked,this,&BrPrint3D::startPrintJob);
    connect(ui->bt_play,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(ui->bt_play,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::setPlayStatus);
    connect(ui->_ManualControl,&ManualControlWidget::disableCbExtruderQnt,ui->_PrinterSettings,&PrinterSettingsWidget::disableExtrudersQntCb);
    connect(ui->bt_pause,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::pausePrintJob);
    connect(ui->bt_pause,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(ui->bt_stop,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::stopPrintJob);
    connect(ui->bt_stop,&BigButton::clicked,this,&BrPrint3D::stopPrintJob);
    connect(ui->bt_stop,&BigButton::clicked,this,&BrPrint3D::changeIcon);
    connect(ui->bt_stopOnEmergency,&BigButton::clicked,ui->_ManualControl,&ManualControlWidget::stopOnEmergency);
    connect(ui->bt_hide,&QPushButton::clicked,this,&BrPrint3D::hidePrinterSettings);
    connect(ui->_ManualControl,&ManualControlWidget::checkConnectButton,ui->bt_connect,&BigButton::setChecked);
    connect(ui->_ManualControl,&ManualControlWidget::checkConnectButton,this,&BrPrint3D::changeIcon);
    connect(ui->_PrinterSettings,&PrinterSettingsWidget::updateCube,ui->vtkView,&vtkWidget::updateCube);
    connect(ui->vtkView,&vtkWidget::layersCount,ui->_ManualControl,&ManualControlWidget::setLayersCount);
    connect(ui->vtkView,&vtkWidget::layersCount,ui->_ManualControl,&ManualControlWidget::setLayersCount);
    connect(ui->_ManualControl,&ManualControlWidget::showCarTravels,ui->vtkView,&vtkWidget::showCarTravels);
    connect(ui->actionAbout,&QAction::triggered,this,&BrPrint3D::showDialogs);
    connect(ui->actionLegalWarning,&QAction::triggered,this,&BrPrint3D::showDialogs);
    connect(ui->actionHelp,&QAction::triggered,this,&BrPrint3D::showDialogs);
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
    ui->bt_play->setEnabled(b);
    ui->bt_pause->setEnabled(b);
    ui->bt_stop->setEnabled(b);
    ui->bt_stopOnEmergency->setEnabled(b);
}

void BrPrint3D::openFile()
{   QString types(QStringLiteral("*.gcode"));
    filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), types);
    QString filePathSuffix = QFileInfo(filePath).completeSuffix().toLower();
    if (!filePath.isEmpty() && filePathSuffix == QLatin1String("gcode")) {
        QFile gcode(filePath);
        if (!gcode.open(QFile::ReadOnly | QFile::Text)) {
            return;
        }
        QTextStream in(&gcode);
        QString text = in.readAll();
        ui->vtkView->renderGcode(text);
        if (ui->bt_connect->isChecked())
            ui->bt_play->setEnabled(true);
        ui->_ManualControl->setFilCount(filePath);
        ui->_ManualControl->setGcodePreview(text);
    }
}

void BrPrint3D::connectPrinter(bool checked)
{
    if (checked){
        psettings = ui->_PrinterSettings->getCurrentSettings();
        ui->_ManualControl->constructPrinterObject(psettings);
        ui->bt_play->setEnabled(false);
        ui->bt_pause->setEnabled(false);
        ui->bt_stop->setEnabled(false);
    } else {
        ui->_ManualControl->destructPrinterObject();
    }
}

void BrPrint3D::startPrintJob(bool checked)
{
    if (checked) {
        ui->_ManualControl->startPrintJob(filePath);
        ui->bt_play->setEnabled(false);
        ui->bt_pause->setEnabled(true);
        ui->bt_stop->setEnabled(true);
    }
}
void BrPrint3D::stopPrintJob()
{
    ui->bt_play->setEnabled(true);
    ui->bt_play->setChecked(false);
    ui->bt_play->setIcon(QIcon(":/Icons/Icons/play.png"));
    ui->bt_pause->setEnabled(false);
    ui->bt_stop->setEnabled(false);
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
{   BigButton *btn = qobject_cast<BigButton*>(sender());
    if( btn == ui->bt_play ) {
        if (checked){
            // use btn_play->setEnabled();
            QIcon icon(":/Icons/Icons/playOnClick.png");
            QPixmap pix(":/Icons/Icons/playOnClick.png");
            icon.addPixmap(pix,QIcon::Disabled,QIcon::Off);
            ui->bt_play->setIcon(icon);
        } else {
            ui->bt_play->setIcon(QIcon(":/Icons/Icons/play.png"));
            ui->bt_play->setChecked(false);
        }
    } else if (btn == ui->bt_pause) {
        if (checked) {
            ui->bt_pause->setIcon(QIcon(":/Icons/Icons/pauseOnClick.png"));
        } else {
            ui->bt_pause->setIcon(QIcon(":/Icons/Icons/pause.png"));
        }
    } else if (btn == ui->bt_connect) {
        if (checked){
            ui->bt_connect->setIcon(QIcon(":/Icons/Icons/connectOnClick.png"));
        } else {
            ui->bt_connect->setIcon(QIcon(":/Icons/Icons/connect.png"));
        }
    }
}

void BrPrint3D::showDialogs(bool b)
{
    QAction *act = qobject_cast<QAction*>(sender());
    if(act == ui->actionAbout && !b){
        aboutBrPrint w;
        w.exec();
    }else if(act == ui->actionLegalWarning && !b){
        LegalWarning w;
        w.exec();
    }else if(act == ui->actionHelp && !b){
        Help w;
        w.exec();
    }
}
