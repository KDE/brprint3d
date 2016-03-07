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
#include "PrinterSettingsWidget.h"
#include "ui_PrinterSettingsWidget.h"

PrinterSettingsWidget::PrinterSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrinterSettingsWidget)
{
    ui->setupUi(this);
    connect(ui->ck_PrintLog,&QCheckBox::toggled,this,&PrinterSettingsWidget::printLogStatusChanged);
    connect(ui->tb_AreaPrintX,&QSpinBox::editingFinished,this,&PrinterSettingsWidget::sendValue);
    connect(ui->tb_AreaPrintY,&QSpinBox::editingFinished,this,&PrinterSettingsWidget::sendValue);
    connect(ui->tb_AreaPrintZ,&QSpinBox::editingFinished,this,&PrinterSettingsWidget::sendValue);
    connect(&timer,&QTimer::timeout,this,&PrinterSettingsWidget::locateArduino);
    connect(ui->bt_SaveSettings,&QPushButton::clicked,this,&PrinterSettingsWidget::saveSettings);
    connect(ui->cb_PrinterSettings,&QComboBox::currentTextChanged,this,&PrinterSettingsWidget::printerSettingsEvent);
}

PrinterSettingsWidget::~PrinterSettingsWidget()
{
    delete ui;
}

void PrinterSettingsWidget::init()
{   timer.start(2000);
    //Load the previous configs if them exists
    QStringList groups;
    settings.beginGroup("Printer_Configs");
    groups = settings.childGroups();
    settings.endGroup();
    ui->cb_PrinterSettings->addItems(groups);
    if(!groups.isEmpty()){
        pSettings = loadSettings(ui->cb_PrinterSettings->currentText());
        setSettings(pSettings);
    }

}
void PrinterSettingsWidget::setSettings(PrinterSettings p){

    //Connection Tab
    ui->cb_ConnectionType->setCurrentText(p.connectionType);
    ui->cb_TransmitionRate->setCurrentText(QString::number(p.transmissionRate));
    ui->cb_Firmware->setCurrentText(p.firmwareType);
    ui->cb_CacheSize->setCurrentText(QString::number(p.cacheSize));

    //Resets
    ui->ck_ResetOnConnect->setChecked(p.resetOnConnect);
    ui->ck_PrintLog->setChecked(p.printLog);

    //Printer Tab
    ui->tb_RateMoviment->setValue(p.rateMoviment);
    ui->tb_FeedZ->setValue(p.feedZ);
    ui->tb_ExtruderSpeed_mm->setValue(p.extruderSpeed);
    ui->tb_ExtruderMaxVol->setValue(p.extruderMAXVol);
    ui->tb_SpeedRetraction->setValue(p.extruderRetraction);
    ui->tb_BedTemperature->setValue(p.bedTemperature);
    ui->tb_ExtruderTemperature->setValue(p.extruderTemperature);
    ui->tb_AreaPrintX->setValue(p.areaX);
    ui->tb_AreaPrintY->setValue(p.areaY);
    ui->tb_AreaPrintZ->setValue(p.areaZ);

    //Extruder Tab
    ui->tb_ExtruderMaxTemp->setValue(p.extruderMAXTemp);
    ui->tb_BedMaxTemp->setValue(p.bedMAXTemp);
    emit updateBed(p.areaX,p.areaY,p.areaZ);
}


//This action save the configs insert by the user on Printer Configs in Ini File
void PrinterSettingsWidget::saveSettings(){
    bool ok;
    QString name = QInputDialog::getText(this, tr("Insert the name of the setting: "),tr("Name:"),QLineEdit::Normal,"ex.: Graber1",&ok);
    settings.beginGroup("Printer_Configs");
    if(ok && !name.isEmpty())
    {   PrinterSettings p = getCurrentSettings();
        settings.beginGroup(name);
        //Conexao
        settings.setValue("Firmware",p.firmwareType);
        settings.setValue("ResetOnConnect",p.resetOnConnect);
        settings.setValue("CacheSize",p.cacheSize);
        settings.setValue("TransmissionRate",p.transmissionRate);
        settings.setValue("PrinterLog",p.printLog);
        //Impressora
        settings.setValue("RateMoviment",p.rateMoviment);
        settings.setValue("FeedZ",p.feedZ);
        settings.setValue("ExtruderSpeed",p.extruderSpeed);
        settings.setValue("ExtruderRetraction",p.extruderRetraction);
        settings.setValue("BedTemperature",p.bedTemperature);
        settings.setValue("ExtruderTemperature",p.extruderTemperature);
        settings.setValue("AreaX",p.areaX);
        settings.setValue("AreaY",p.areaY);
        settings.setValue("AreaZ",p.areaZ);
        //Extrusor
        settings.setValue("ExtruderMaxTemp",p.extruderMAXTemp);
        settings.setValue("BedMaxTemp",p.bedMAXTemp);
        settings.setValue("VolumeMax",p.extruderMAXVol);
        settings.endGroup();

    }
    settings.endGroup();
    QStringList groups;
    settings.beginGroup("Printer_Configs");
    groups = settings.childGroups();
    settings.endGroup();
    ui->cb_PrinterSettings->clear();
    ui->cb_PrinterSettings->addItems(groups);
}

PrinterSettings PrinterSettingsWidget::loadSettings(QString q){
       settings.beginGroup("Printer_Configs");
       settings.beginGroup(q);
       PrinterSettings p;
       //Connection
       p.connectionType = settings.value("ConnectionType","USB").toString();
       p.transmissionRate = settings.value("TransmissionRate","115200").toInt();
       p.firmwareType = settings.value("Firmware","Repetier").toString();
       p.cacheSize = settings.value("CacheSize","127").toInt();
       p.resetOnConnect = settings.value("ResetOnConnect",2).toInt();
       p.printLog = settings.value("PrinterLog",0).toInt();

       //Printer
       p.rateMoviment = settings.value("RateMoviment",0).toInt();
       p.feedZ = settings.value("FeedZ",0).toInt();
       p.extruderSpeed = settings.value("ExtruderSpeed",0).toInt();
       p.extruderRetraction = settings.value("ExtruderRetraction",0).toInt();
       p.extruderTemperature = settings.value("ExtruderTemperature",210).toInt();
       p.bedTemperature = settings.value("BedTemperature",110).toInt();
       p.areaX = settings.value("AreaX",200).toInt();
       p.areaY = settings.value("AreaY",200).toInt();
       p.areaZ = settings.value("AreaZ",200).toInt();

       //Extruder
       p.extruderMAXTemp = settings.value("ExtruderMaxTemp",230).toInt();
       p.bedMAXTemp = settings.value("BedMaxTemp",120).toInt();
       p.extruderMAXVol = settings.value("VolumeMax",0).toInt();
       settings.endGroup();
       settings.endGroup();
       return p;

}

PrinterSettings PrinterSettingsWidget::getCurrentSettings()
{
    PrinterSettings p;
    p.connectionPort = ui->cb_ConnectionPort->currentText();
    p.connectionType = ui->cb_ConnectionType->currentText();
    p.transmissionRate = ui->cb_TransmitionRate->currentText().toInt();
    p.firmwareType = ui->cb_Firmware->currentText();
    p.cacheSize = ui->cb_CacheSize->currentText().toInt();
    p.resetOnConnect = ui->ck_ResetOnConnect->isChecked();
    p.printLog = ui->ck_PrintLog->isChecked();
    p.rateMoviment = ui->tb_RateMoviment->value();
    p.feedZ = ui->tb_FeedZ->value();
    p.extruderSpeed = ui->tb_ExtruderSpeed_mm->value();
    p.extruderRetraction = ui->tb_SpeedRetraction->value();
    p.extruderTemperature = ui->tb_ExtruderTemperature->value();
    p.bedTemperature = ui->tb_BedTemperature->value();
    p.areaX = ui->tb_AreaPrintX->value();
    p.areaY = ui->tb_AreaPrintY->value();
    p.areaZ = ui->tb_AreaPrintZ->value();
    p.extruderMAXTemp = ui->tb_ExtruderMaxTemp->value();
    p.extruderMAXVol = ui->tb_ExtruderMaxVol->value();
    p.bedMAXTemp = ui->tb_BedMaxTemp->value();
    return p;


}

int PrinterSettingsWidget::getPortStatus()
{
       return ui->cb_ConnectionPort->count();
}

void PrinterSettingsWidget::locateArduino()
{   actPortList.clear();
    QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();
    if(!serialPortInfoList.isEmpty())
    {   foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList) {
        actPortList.append("/dev/"+serialPortInfo.portName());
        }
        if(antPortList.isEmpty())
        {
            antPortList = actPortList;
            ui->cb_ConnectionPort->addItems(actPortList);
        }else if(actPortList!=antPortList){
            ui->cb_ConnectionPort->clear();
            ui->cb_ConnectionPort->addItems(actPortList);
            antPortList = actPortList;
        }


    }

}
void PrinterSettingsWidget::printLogStatusChanged(){
    emit s_printLogStatus(ui->ck_PrintLog->isChecked());
}
void PrinterSettingsWidget::sendValue(){
    QSpinBox *btn = qobject_cast<QSpinBox*>(sender());
    if(btn==ui->tb_AreaPrintX)
        emit updateCube(ui->tb_AreaPrintX->value(),'X');
    if(btn==ui->tb_AreaPrintY)
        emit updateCube(ui->tb_AreaPrintY->value(),'Y');
    if(btn==ui->tb_AreaPrintZ)
        emit updateCube(ui->tb_AreaPrintZ->value(),'Z');

}

void PrinterSettingsWidget::printerSettingsEvent(QString s)
{
    PrinterSettings p = loadSettings(s);
    setSettings(p);
}
