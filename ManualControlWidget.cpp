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
#include "ManualControlWidget.h"
#include "ui_ManualControlWidget.h"

ManualControlWidget::ManualControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualControlWidget)
{
    ui->setupUi(this);
    connect(&timer,&QTimer::timeout,this,&ManualControlWidget::updateTemp);
    connect(&timer,&QTimer::timeout,this,&ManualControlWidget::isPrintJobRunning);
    connect(ui->ck_carTravels,&QCheckBox::clicked,this,&ManualControlWidget::showCarTravels);
    connect(ui->sp_bedTemp,&QSpinBox::editingFinished,this,&ManualControlWidget::setNewBedTemp);
    connect(ui->bt_bedHeat,&QPushButton::clicked,this,&ManualControlWidget::startBed);
    connect(ui->sp_extruderTemp,&QSpinBox::editingFinished,this,&ManualControlWidget::setNewExtruderTemp);
    connect(ui->bt_extruderHeat,&QPushButton::clicked,this,&ManualControlWidget::startExtruders);
}

ManualControlWidget::~ManualControlWidget()
{
    delete ui;
}

void ManualControlWidget::init()
{   ui->ManualControlTab->setDisabled(true);
    ui->gcodeText->setPlainText(tr("No Open File."));
    /*if(extrudersInUse < 2){
        ui->extruderMonitorTab->setHidden(true);//Dont work, why???
        ui->extruderMonitorTab->setDisabled(true);
    }else{
        ui->gb_extruderOne->setDisabled(true);
        insertExtruderItem(extrudersInUse);
    }*/
}
void ManualControlWidget::constructPrinterObject(PrinterSettings pSettings)
{
    int maxX, maxY, maxZ, transmissionRate, bufferSize;
    std::string connectionPort;
    bool resetOnconnect,isCommaDecimalMark;
    if(pSettings.areaX==0 || pSettings.areaY==0 || pSettings.areaZ==0)
    {
        QMessageBox msg;
        msg.setText(tr("Make sure you have all the necessary settings for connection!"));
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        emit checkConnectButton(false);
    }
    else
    {   ui->ManualControl->setEnabled(true);
        QLocale locale;
        QChar c = locale.decimalPoint();
        if(c=='.')
            isCommaDecimalMark = false;
        else
            isCommaDecimalMark = true;
        maxX = pSettings.areaX;
        maxY = pSettings.areaY;
        maxZ = pSettings.areaZ;
        transmissionRate = pSettings.transmissionRate;
        connectionPort = pSettings.connectionPort.toStdString();
        bufferSize = pSettings.cacheSize;
        resetOnconnect = pSettings.resetOnConnect;
        try{
            QMessageBox msg;
            printerObject = new Repetier(transmissionRate,connectionPort,bufferSize,maxX,maxY,maxZ,resetOnconnect,isCommaDecimalMark);
            extruderQnt = printerObject->getNoOfExtruders();
            ui->extruderControlWidget->getPrinterObject(printerObject);
            timer.start(1000);
            ui->ManualControlTab->setEnabled(true);
            emit enablePlayButton(true);

            //TODO: Please try to inform the user using another method, a popup on the user face is terrible.
            //Try to use the KDE Library "InformationWidget"
            msg.setText(tr("Successful Connection"));
            msg.setIcon(QMessageBox::Information);
            msg.exec();
        }
        catch(std::string exc){
            QMessageBox msg;
            QString e =QString::fromUtf8(exc.c_str());
            msg.setText(e);
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
            ui->ManualControlTab->setEnabled(false);
            emit checkConnectButton(false);
        }
    }

}
void ManualControlWidget::destructPrinterObject()
{   timer.stop();
    if(ui->bt_bedHeat->isChecked()){
        printerObject->setBedTemp(0);
    }
    if(ui->bt_extruderHeat->isChecked()){
        for(int i=0;i<extrudersInUse;i++)
            printerObject->setExtrTemp(i,0);
    }
    printerObject->~Repetier();
    ui->ManualControlTab->setDisabled(true);
}

void ManualControlWidget::startBed(bool checked)
{
    if (checked) {
        printerObject->setBedTemp(ui->sp_bedTemp->value());
    } else {
        printerObject->setBedTemp(0);
    }
}

void ManualControlWidget::startExtruders(bool checked)
{   if(extrudersInUse == 1 && checked){
            printerObject->setExtrTemp(0,ui->sp_extruderTemp->value());
    }else/*Heat OFF*/{
        printerObject->setExtrTemp(0,0);
    }
}

void ManualControlWidget::setNewBedTemp(){
    if(playStatus && ui->bt_bedHeat->isChecked())
        printerObject->setBedTemp(ui->sp_bedTemp->value());
}

void ManualControlWidget::setNewExtruderTemp(){
    if(playStatus && ui->bt_extruderHeat->isChecked()){
        printerObject->setExtrTemp(0,ui->sp_extruderTemp->value());
    }
}

void ManualControlWidget::setPlayStatus(bool b){
    playStatus = b;
}

void ManualControlWidget::updateTemp()
{   //Bed
    double bedCurrTemp = printerObject->getBedTemp();
    ui->lb_bedCurrTemp->setText(QString::number(bedCurrTemp)+" ºC");
    //Extruders
    double *extCurrTemp = printerObject->getAllExtrudersTemp();
    ui->lb_extruderCurrTemp->setText(QString::number(extCurrTemp[0])+" ºC");
}

void ManualControlWidget::setGcodePreview(const QString& t){
    ui->gcodeText->setPlainText(t);
}

void ManualControlWidget::startPrintJob(const QString& filePath){
   QMessageBox msg;
   try {    std::string path = filePath.toStdString();
            printerObject->openFile(path,printLogStatus);
            printerObject->startPrintJob(true);
            msg.setText(tr("Print job started!"));
            msg.exec();
            emit disablePositionButtons(true);
       }
   catch (std::string exc){

           msg.setIcon(QMessageBox::Critical);
           QString str = QString::fromUtf8(exc.c_str());
           msg.setText(str);
           msg.exec();

          }
}

void ManualControlWidget::setPrintLogStatus(bool b){
    printLogStatus = b;
}

void ManualControlWidget::isPrintJobRunning()
{   bool b = printerObject->isPrintJobRunning();
    //This function return if the print job is finalized
    QMessageBox msg;
    if (!b && playStatus && !pauseStatus) {
        msg.setText("Print job finish!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
        disconnect(&timer,&QTimer::timeout,this,&ManualControlWidget::isPrintJobRunning);
    }
}

void ManualControlWidget::pausePrintJob(bool b){
   QMessageBox msg;
    if (b){
        printerObject->stopPrintJob();
        msg.setText("Print job paused!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
       }
    else{
          printerObject->startPrintJob(false);
       }
    pauseStatus = b;
}

void ManualControlWidget::stopPrintJob(){
    QMessageBox msg;
    printerObject->stopPrintJob();
    printerObject->closeFile();
    try {
        if(printerObject->getBedTemp()!=0)
            printerObject->setBedTemp(0);
    }
    catch(std::string exc){

        msg.setIcon(QMessageBox::Critical);
        QString str = QString::fromUtf8(exc.c_str());
        msg.setText(str);
        msg.exec();

    }
    try{
    for(int i=0;i<extrudersInUse;i++)
        printerObject->setExtrTemp(i,0);
    }
    catch(std::string exc){
        msg.setIcon(QMessageBox::Critical);
        QString str = QString::fromUtf8(exc.c_str());
        msg.setText(str);
        msg.exec();
    }
    emit disablePositionButtons(false);
}

void ManualControlWidget::stopOnEmergency(){
    QMessageBox msg;
    msg.setText("Emergency Stop Clicked, click on 'Ok' and wait!");
    msg.setIcon(QMessageBox::Critical);
    msg.exec();
    try{
        printerObject->scramPrinter();
        emit disablePositionButtons(false);
    }
    catch(std::string exc){
        QString str = QString::fromUtf8(exc.c_str());
        msg.setText(str);
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }
}

void ManualControlWidget::setLayersCount(int l){
    ui->lb_layerCounter->setText(QString::number(l));
    ui->sl_layersFirst->setMaximum(l);
    ui->sl_layersLast->setMaximum(l);
}

void ManualControlWidget::setFilCount(const QString& filePath){
    double totalSize;
    long timeNeed;
    try{
        FilCount fil = FilCount(filePath.toStdString());
        totalSize = fil.getTotalSize();
        ui->lb_filamentQnt->setText(QString::number(totalSize));
        //timeNeed = fil.getTimeInSeconds(ui->ds_printSpeed->value());
        timeNeed /=60;
        ui->lb_estimatedTime->setText(QString::number(timeNeed));
    }
    catch(std::string exc){
        QMessageBox msg;
        QString str = QString::fromUtf8(exc.c_str());
        msg.setText(str);
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    }
}
