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
    connect(ui->bt_Bed,&QPushButton::clicked,this,&ManualControlWidget::startBed);
    connect(ui->bt_extruder0,&QPushButton::clicked,this,&ManualControlWidget::startExtruders);
    connect(ui->ds_bedTemp,&QDoubleSpinBox::editingFinished,this,&ManualControlWidget::setNewBedTemp);
    connect(ui->ds_extruderTemp,&QDoubleSpinBox::editingFinished,this,&ManualControlWidget::setNewExtruderTemp);
    connect(this,&ManualControlWidget::disablePositionButtons,ui->extruderControlWidget,&ExtruderControlWidget::disablePositionsButtons);

    connect(ui->ds_printSpeed,&QSpinBox::editingFinished,this,&ManualControlWidget::spinEditFinished);
    connect(ui->ds_filamentFlow,&QSpinBox::editingFinished,this,&ManualControlWidget::spinEditFinished);
    connect(ui->ds_coolerFan,&QSpinBox::editingFinished,this,&ManualControlWidget::spinEditFinished);

    connect(ui->sl_printSpeed,&QSlider::valueChanged, this, &ManualControlWidget::sliderValueChanged);
    connect(ui->sl_filamentFlow,&QSlider::valueChanged,this,&ManualControlWidget::sliderValueChanged);
    connect(ui->sl_coolerFan,&QSlider::valueChanged,this,&ManualControlWidget::sliderValueChanged);
    connect(&timer,&QTimer::timeout,this,&ManualControlWidget::updateTemp);
    connect(&timer,&QTimer::timeout,ui->extruderControlWidget,&ExtruderControlWidget::updatePos);
    connect(&timer,&QTimer::timeout,this,&ManualControlWidget::isPrintJobRunning);
    connect(ui->ck_carTravels,&QCheckBox::clicked,this,&ManualControlWidget::showCarTravels);

}

ManualControlWidget::~ManualControlWidget()
{
    delete ui;
}

void ManualControlWidget::init()
{   ui->ManualControlTab->setDisabled(true);
    ui->GCodePreview->setPlainText(tr("No Open File."));
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
        setInitialMarks();
    }

}
void ManualControlWidget::destructPrinterObject()
{   timer.stop();
    if(ui->bt_Bed->isChecked()){
        printerObject->setBedTemp(0);
        ui->bt_Bed->setChecked(false);
    }
    if(ui->bt_extruder0->isChecked()){
        for(int i=0;i<extrudersInUse;i++)
            printerObject->setExtrTemp(i,0);
        ui->bt_extruder0->setChecked(false);
    }
    printerObject->~Repetier();
    ui->ManualControlTab->setDisabled(true);
}

void ManualControlWidget::startBed(bool checked)
{
    if (checked) {
        printerObject->setBedTemp(ui->ds_bedTemp->value());
    } else {
        ui->bt_Bed->setStyleSheet("");
        printerObject->setBedTemp(0);
    }
}

void ManualControlWidget::startExtruders(bool checked)
{
    if (checked) {
        for(int i=1;i<=extrudersInUse;i++)
            printerObject->setExtrTemp(i-1,ui->ds_extruderTemp->value());

    } else {
        ui->bt_extruder0->setStyleSheet("");
        for(int i = 1; i <= extrudersInUse; i++) { 
            printerObject->setExtrTemp(i-1,0);
            switch (i) {
            case 1: ui->bt_extruder1->setStyleSheet(""); break;
            case 2: ui->bt_extruder2->setStyleSheet(""); break;
            case 3: ui->bt_extruder3->setStyleSheet(""); break;
            case 4: ui->bt_extruder4->setStyleSheet(""); break;
            }
        }
    }

}

void ManualControlWidget::disableExtrudersButtons(bool checked)
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    ui->bt_extruder1->setEnabled(btn == ui->bt_extruder1);
    ui->bt_extruder2->setEnabled(btn == ui->bt_extruder2);
    ui->bt_extruder3->setEnabled(btn == ui->bt_extruder3);
    ui->bt_extruder4->setEnabled(btn == ui->bt_extruder4);
}

void ManualControlWidget::setNewBedTemp(){
    if(playStatus && ui->bt_Bed->isChecked())
        printerObject->setBedTemp(ui->ds_bedTemp->value());
}
void ManualControlWidget::setPlayStatus(bool b){
    playStatus = b;
}
void ManualControlWidget::setNewExtruderTemp(){
    if(playStatus && ui->bt_extruder0->isChecked())
    {
        for(int i=0;i<extrudersInUse;i++)
            printerObject->setExtrTemp(i,ui->ds_extruderTemp->value());
    }
}


void ManualControlWidget::setInitialMarks()
{

}

//This slot update on UI the value of Temperatures of the Bed and Extruders
//There some inconsistency on the tests here - CHECK!
void ManualControlWidget::updateTemp()
{   //This function update the printer temperatures on the screen
    double temp_Bed = printerObject->getBedTemp();
    double tempExtruders[5];
    for (int i = 0; i <extrudersInUse; i++) {
         tempExtruders[i] =  printerObject->getExtruderTemp(i);
    }
    //Change bed temperatures
    ui->sl_bed->setValue(temp_Bed);
    ui->lb_bedTemp->setText(QString::number(temp_Bed));
    //Update Color Status
    if(ui->bt_Bed->isChecked())
    {
        if(ui->sl_bed->value()>=ui->ds_bedTemp->value())
            ui->bt_Bed->setStyleSheet("background-color:red;");
        else
            ui->bt_Bed->setStyleSheet("background-color:yellow;");
     }
     //If the printer is using one extruder, the slider will belongs all the time to extruder 1
     if(extrudersInUse==1)
     {
        ui->sl_extruder->setValue(tempExtruders[0]);//Set temperature on slider
        ui->lb_extruderTemp0->setText(QString::number(tempExtruders[0]));//Set Label of slider
        ui->lb_extruderTemp1->setText(QString::number(tempExtruders[0]));//Set label on Ext 1
        //Change color status
        if(ui->bt_extruder0->isChecked())
        {   if(ui->lb_extruderTemp1->text().toFloat()>=ui->ds_extruderTemp->value())
            {    ui->bt_extruder1->setStyleSheet("background-color:red;");
                 ui->bt_extruder0->setStyleSheet("background-color:red;");
            }
            else
            {    ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                 ui->bt_extruder0->setStyleSheet("background-color:yellow;");
            }
        }

     }
     else
     {  //Change extruders temp
        ui->bt_extruder0->setStyleSheet("background-color:green;");
        for(int i=1;i<=extrudersInUse;i++)
        {
            switch (i)
            {
                case 1:
                {   if(ui->bt_extruder1->isChecked())//Slider belongs to extruder 1
                    {
                        ui->sl_extruder->setValue(tempExtruders[i-1]); //Set Slider value
                        ui->lb_extruderTemp0->setText(QString::number(tempExtruders[i-1]));//Set Label of slider
                    }
                    //Refresh Color Status
                    if(ui->bt_extruder0->isChecked())
                    {   if(ui->lb_extruderTemp1->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())
                            ui->bt_extruder1->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                    }
                    ui->lb_extruderTemp1->setText(QString::number(tempExtruders[i-1]));//Set label extruder value

                }break;
                case 2:
                {   if(ui->bt_extruder2->isChecked())//Slider belongs to extruder two
                    {   ui->sl_extruder->setValue(tempExtruders[i-1]);
                        ui->lb_extruderTemp0->setText(QString::number(tempExtruders[i-1]));//Set Label of slider
                    }
                   //Refresh Color Status
                   if(ui->bt_extruder0->isChecked())
                   {    if(ui->lb_extruderTemp2->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())//Refresh Color Status
                            ui->bt_extruder2->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder2->setStyleSheet("background-color:yellow;");
                   }
                   ui->lb_extruderTemp2->setText(QString::number(tempExtruders[i-1]));
                }break;
                case 3:
                {  if(ui->bt_extruder3->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(tempExtruders[i-1]);
                       ui->lb_extruderTemp0->setText(QString::number(tempExtruders[i-1]));//Set Label of slider
                   }

                    //Refresh Color Status
                   if(ui->bt_extruder0->isChecked())
                   {
                       if(ui->lb_extruderTemp3->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())//Refresh Color Status
                            ui->bt_extruder3->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder3->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp3->setText(QString::number(tempExtruders[i-1]));
                }break;
                case 4:
                {  if(ui->bt_extruder4->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(tempExtruders[i-1]);
                       ui->lb_extruderTemp0->setText(QString::number(tempExtruders[i-1]));//Set Label of slider
                   }
                   //Change Color Status
                   if(ui->bt_extruder0->isChecked())
                   {
                        if(ui->lb_extruderTemp4->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())//Refresh Color Status
                            ui->bt_extruder4->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder4->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp4->setText(QString::number(tempExtruders[i-1]));
                }break;
                default:
                    break;
                }
            }
}
}
void ManualControlWidget::hideExtruders(int e)
{
    switch (e){
    case 1:{   
        ui->wg_group2->hide();
        ui->wg_group3->hide();
        ui->wg_group4->hide();
    }break;
    case 2:{   
        ui->wg_group3->hide();
        ui->wg_group4->hide();
    }break;
    case 3:{
        ui->wg_group4->hide();
    }break;

    default:
        break;
    }
}
void ManualControlWidget::setExtrudersInUse(int e)
{
    extrudersInUse = e;
    hideExtruders(e);
}
void ManualControlWidget::setGcodePreview(const QString& t){
    ui->GCodePreview->setPlainText(t);
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
        emit disableCbExtruderQnt(false);
        emit disableExtrudersButtons(false);
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

void ManualControlWidget::spinEditFinished(){
    QSpinBox *btn = qobject_cast<QSpinBox*>(sender());
    if(btn==ui->ds_printSpeed){
        int speed = ui->ds_printSpeed->value();
        printerObject->setFeedRate(speed);
        ui->sl_printSpeed->setValue(speed);
        ui->lb_printSpeed->setText(QString::number(speed));
    }
    if(btn==ui->ds_filamentFlow){
        int flow = ui->ds_filamentFlow->value();
        printerObject->setFlowRate(flow);
        ui->sl_filamentFlow->setValue(flow);
        ui->lb_filFlowValue->setText(QString::number(flow));

    }
    if(btn==ui->ds_coolerFan)
    {
        int fan = ui->ds_coolerFan->value();
        printerObject->setFanSpeed(fan);
        ui->sl_coolerFan->setValue(fan);
        ui->lb_coolerValue->setText(QString::number(fan));
    }

}
void ManualControlWidget::sliderValueChanged(int v){
    QSlider *btn = qobject_cast<QSlider*>(sender());
    if(btn==ui->sl_printSpeed)
    {
        ui->ds_printSpeed->setValue(v);
        ui->lb_printSpeed->setText(QString::number(v));
        printerObject->setFeedRate(v);
    }
    if(btn==ui->sl_filamentFlow)
    {
        ui->ds_filamentFlow->setValue(v);
        ui->lb_filFlowValue->setText(QString::number(v));
        printerObject->setFlowRate(v);
    }
    if(btn==ui->sl_coolerFan)
    {
        ui->ds_coolerFan->setValue(v);
        ui->lb_coolerValue->setText(QString::number(v));
        printerObject->setFanSpeed(v);
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
        timeNeed = fil.getTimeInSeconds(ui->ds_printSpeed->value());
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
