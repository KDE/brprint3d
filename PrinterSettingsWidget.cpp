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
    connect(ui->tb_AreaPrintX,&QLineEdit::textEdited,this,&PrinterSettingsWidget::sendValue);
    connect(ui->tb_AreaPrintY,&QLineEdit::textEdited,this,&PrinterSettingsWidget::sendValue);
    connect(ui->tb_AreaPrintZ,&QLineEdit::textEdited,this,&PrinterSettingsWidget::sendValue);
}

PrinterSettingsWidget::~PrinterSettingsWidget()
{
    delete ui;
}

void PrinterSettingsWidget::init()
{
    arduino_Listener = new arduinoListener();
    connect(arduino_Listener,SIGNAL(arduinoConnect(bool)),this,SLOT(locateArduino(bool)));
    arduino_Listener->start();


    /*this->settings = settings;
    //Load the previous configs if them exists
    QStringList groups;
    settings->beginGroup("Printer_Configs");
    groups = settings->childGroups();
    settings->endGroup();
    ui->cb_Printer->addItems(groups);
    if(!groups.isEmpty())
    {   //Criar init printer configs
        QString a = ui->cb_Printer->currentText();
        PrinterSettings p = loadConfigs(a);
        //Connection Tab
        ui->cb_Connection_Type->setCurrentText(p.connectionType);
        ui->cb_Transmition_Rate->setCurrentText(p.transmissionRate);
        ui->cb_Firmware->setCurrentText(p.firmwareType);
        ui->cb_Cache_Size->setCurrentText(p.cacheSize);

        //Resets
        ui->ck_ResetonConnect->setChecked(p.resetOnConnect);
        ui->ck_ResetonEmergency->setChecked(p.resetOnEmergency);
        ui->ck_PrintLog->setChecked(p.printLog);

        //Printer Tab
        ui->tb_RateMoviment->setText(p.rateMoviment);
        ui->tb_FeedZ->setText(p.feedZ);
        ui->tb_ExtSpeedmm->setText(p.extruderSpeedMM);
        ui->tb_ExtSpeedSec->setText(p.extruderSpeedS);
        ui->tb_ExtMaxVol->setText(p.extruderMAXVol);
        ui->tb_RetractionSpeed->setText(p.extruderRetraction);
        ui->tb_BedTemp->setText(p.bedTemperature);
        ui->tb_ExtTemperature->setText(p.extruderTemperature);
        ui->tb_AreaPrintX->setText(p.areaX);
        ui->tb_AreaPrintY->setText(p.areaY);
        ui->tb_AreaPrintZ->setText(p.areaZ);

        //Extruder Tab
        ui->cb_ExtruderQnt->setCurrentText(p.extruderQnt);
        ui->tb_ExtMaxTemp->setText(p.extruderMAXTemp);
        ui->tb_BedMaxTemp->setText(p.bedMAXTemp);
    }*/

}
/*
//This action save the configs insert by the user on Printer Configs in Ini File
void PrinterSettingsWidget::on_bt_SaveConfig_clicked() //Save actual configs
{   bool ok;
    QString name = QInputDialog::getText(this, tr("Insert the name of config: "),tr("Name:"),QLineEdit::Normal,"ex.: Graber1",&ok);
    this->settings->beginGroup("Printer_Configs");
    if(ok && !name.isEmpty())
    {   PrinterSettings p = this->getCurrentSettings();
        this->settings->beginGroup(name);
        //Conexao
        this->settings->setValue("Firmware",p.firmwareType);
        this->settings->setValue("ResetOnConnect",p.resetOnConnect);
        this->settings->setValue("ResetonEmergency",p.resetOnEmergency);
        this->settings->setValue("CacheSize",p.cacheSize);
        this->settings->setValue("TransmissionRate",p.transmissionRate);
        this->settings->setValue("PrinterLog",p.printLog);
        //Impressora
        this->settings->setValue("RateMoviment",p.rateMoviment);
        this->settings->setValue("FeedZ",p.feedZ);
        this->settings->setValue("ExtruderSpeedMM",p.extruderSpeedMM);
        this->settings->setValue("ExtruderSpeedSec",p.extruderSpeedS);
        this->settings->setValue("ExtruderRetraction",p.extruderRetraction);
        this->settings->setValue("BedTemperature",p.bedTemperature);
        this->settings->setValue("ExtruderTemperature",p.extruderTemperature);
        this->settings->setValue("AreaX",p.areaX);
        this->settings->setValue("AreaY",p.areaY);
        this->settings->setValue("AreaZ",p.areaZ);
        //Extrusor
        this->settings->setValue("ExtruderQnt",p.extrudersInUse);
        this->settings->setValue("ExtruderMaxTemp",p.extruderMAXTemp);
        this->settings->setValue("BedMaxTemp",p.bedMAXTemp);
        this->settings->setValue("VolumeMax",p.extruderMAXVol);
        this->settings->endGroup();

    }
    this->settings->endGroup();
    QStringList groups;
    this->settings->beginGroup("Printer_Configs");
    groups = this->settings->childGroups();
    this->settings->endGroup();
    ui->cb_Printer->clear();
    ui->cb_Printer->addItems(groups);
}

PrinterSettings PrinterSettingsWidget::loadConfigs(QString q)
{
        settings->beginGroup("Printer_Configs");
        settings->beginGroup(q);
        PrinterSettings p;
        //Connection
       p.connectionType = settings->value("ConnectionType","USB").toString();
       p.transmissionRate = settings->value("TransmissionRate","115200").toString();
       p.firmwareType = settings->value("Firmware","Repetier").toString();
       p.cacheSize = settings->value("CacheSize","127").toString();
       p.resetOnConnect = settings->value("ResetOnConnect",2).toInt();
       p.resetOnEmergency = settings->value("ResetonEmergency",0).toInt();
       p.printLog = settings->value("PrinterLog",0).toInt();

        //Printer
       p.rateMoviment = settings->value("RateMoviment",0).toString();
       p.feedZ = settings->value("FeedZ",0).toString();
       p.extruderSpeedMM = settings->value("ExtruderSpeedMM",0).toString();
       p.extruderSpeedS = settings->value("ExtruderSpeedSec",0).toString();
       p.extruderRetraction = settings->value("ExtruderRetraction",0).toString();
       p.extruderTemperature = settings->value("ExtruderTemperature",210).toString();
       p.bedTemperature = settings->value("BedTemperature",110).toString();
       p.areaX = settings->value("AreaX",0).toString();
       p.areaY = settings->value("AreaY",0).toString();
       p.areaZ = settings->value("AreaZ",0).toString();

        //Extruder
       p.extruderQnt = settings->value("ExtruderQnt",1).toString();
       p.extruderMAXTemp = settings->value("ExtruderMaxTemp",230).toString();
       p.bedMAXTemp = settings->value("BedMaxTemp",120).toString();
       p.extruderMAXVol = settings->value("VolumeMax",0).toString();
        settings->endGroup();
        settings->endGroup();
        return p;

}
//This actions loads the config choose by the user on Printer Configs
void PrinterSettingsWidget::on_cb_Printer_currentTextChanged(const QString &arg1)
{
    loadConfigs(arg1);
}*/
PrinterSettings PrinterSettingsWidget::getCurrentSettings()
{
    PrinterSettings p;
    p.connectionType = ui->cb_ConnectionType->currentText();
    p.connectionPort = ui->cb_ConnectionPort->currentText();
    p.transmissionRate = ui->cb_TransmitionRate->currentText();
    p.firmwareType = ui->cb_Firmware->currentText();
    p.cacheSize = ui->cb_CacheSize->currentText();
    p.resetOnConnect = ui->ck_ResetOnConnect->isChecked();
    p.printLog = ui->ck_PrintLog->isChecked();
    p.rateMoviment = ui->tb_RateMoviment->text();
    p.feedZ = ui->tb_FeedZ->text();
    p.extruderSpeedMM = ui->tb_ExtruderSpeed_mm->text();
    p.extruderSpeedS = ui->tb_ExtruderSpeed_sec->text();
    p.extruderRetraction = ui->tb_SpeedRetraction->text();
    p.extruderTemperature = ui->tb_ExtruderTemperature->text();
    p.bedTemperature = ui->tb_BedTemperature->text();
    p.areaX = ui->tb_AreaPrintX->text();
    p.areaY = ui->tb_AreaPrintY->text();
    p.areaZ = ui->tb_AreaPrintZ->text();
    p.extrudersInUse = ui->cb_ExtruderQnt->currentText().toInt();
    p.extruderMAXTemp = ui->tb_ExtruderMaxTemp->text();
    p.extruderMAXVol = ui->tb_ExtruderMaxVol->text();
    p.bedMAXTemp = ui->tb_BedMaxTemp->text();
    return p;


}
void PrinterSettingsWidget::setConnectionPorts(QStringList p)
{
    ui->cb_ConnectionPort->addItems(p);
}
void PrinterSettingsWidget::disableExtrudersQntCb(bool d)
{
    ui->cb_ExtruderQnt->setDisabled(d);
}

void PrinterSettingsWidget::locateArduino()
{   arduino_Listener->wait(2000);
    arduino_Listener->quit();
    arduino_Listener->deleteLater();
    QStringList ports;
    garbage=std::system("dmesg | grep -i usb > usbport.txt");
    QFile usbport("usbport.txt");
    if(usbport.open(QIODevice::ReadOnly|QIODevice::Text))
    {   QTextStream in(&usbport);
        QString file = in.readAll();
        usbport.close();
        QString port,ant = "\0";
        std::string temp = file.toStdString();
        const char *look = temp.c_str();
        //qDebug()<<QString(word)
        look = strstr(look, "Arduino");
        while(look != nullptr)
        {
            look = strstr(look, "tty");
            for(int i = 0; look[i] != ':'; i++)
                port+=look[i];
            if(ant!=port)
            {   if(port!="ttyACM0" && port!="ttyUSB0")
                {   ports.append("/dev/"+port);
                    ant=port;
                }
            }
            port.clear();
            look = strstr(look, "Arduino");
        }
    }
    if(!ports.isEmpty())
    {   ui->cb_ConnectionPort->addItems(ports);
        QMessageBox msg;
        msg.setText("The arduino is connect at new ports then default, please check on Configs Menu to switch ports!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    }


}

void PrinterSettingsWidget::on_cb_ExtruderQnt_currentTextChanged(const QString &arg1)
{
    extrudersInUse = arg1.toInt();
    emit s_extrudersInUse(extrudersInUse);

}
void PrinterSettingsWidget::printLogStatusChanged(){
    emit s_printLogStatus(ui->ck_PrintLog->isChecked());
}
void PrinterSettingsWidget::sendValue(QString v){
    if(sender()==ui->tb_AreaPrintX)
        emit updateCube(v,'X');
    if(sender()==ui->tb_AreaPrintY)
        emit updateCube(v,'Y');
    if(sender()==ui->tb_AreaPrintZ)
        emit updateCube(v,'Z');

}
