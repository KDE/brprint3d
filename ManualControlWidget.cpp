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

    connect(ui->sl_printSpeed,&QSlider::valueChanged, this, &ManualControlWidget::setValue);
    connect(ui->sl_filamentFlow,&QSlider::valueChanged,this,&ManualControlWidget::setValue);
    connect(ui->sl_coolerFan,&QSlider::valueChanged,this,&ManualControlWidget::setValue);

}

ManualControlWidget::~ManualControlWidget()
{
    delete ui;
}

void ManualControlWidget::init()
{   ui->ManualControlTab->setDisabled(true);
    ui->Slicer->setDisabled(true);
    ui->GCodePreview->setPlainText(tr("No Open File."));

    //If slic3er exists in Ini file, load path, else locate
    pathslicer=QVariant (this->settings.value("slic3r")).toString();
    if(pathslicer.isEmpty())
        locateSlicer();
    else
    {   ui->cb_slicer->addItem("Slic3r");
        ui->bt_addSlicer->setEnabled(false);
    }

    //If cura exists in Ini file, load path, else locate
    pathcura=QVariant (settings.value("cura")).toString();
    if(pathcura.isEmpty())
        locateCura();
    else
        ui->cb_slicer->addItem("Cura Engine");

}
void ManualControlWidget::constructPrinterObject(PrinterSettings pSettings)
{
    QMessageBox msg;
    int maxX, maxY, maxZ, transmissionRate, bufferSize;
    std::string connectionPort;
    bool resetOnconnect,isCommaDecimalMark;
    if(pSettings.areaX.isEmpty() || pSettings.areaY.isEmpty() || pSettings.areaZ.isEmpty())
    {
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
        maxX = pSettings.areaX.toInt();
        maxY = pSettings.areaY.toInt();
        maxZ = pSettings.areaZ.toInt();
        transmissionRate = pSettings.transmissionRate.toInt();
        connectionPort = pSettings.connectionPort.toStdString();
        bufferSize = pSettings.cacheSize.toInt();
        if(pSettings.resetOnConnect==0)
            resetOnconnect = false;
        else
            resetOnconnect = true;


    try{
        printerObject = new Repetier(transmissionRate,connectionPort,bufferSize,maxX,maxY,maxZ,resetOnconnect,isCommaDecimalMark);
        extruderQnt = printerObject->getNoOfExtruders();
        ui->extruderControlWidget->getPrinterObject(printerObject);
        startThreadRoutine();
        ui->ManualControlTab->setEnabled(true);
        emit enablePlayButton(true);
        msg.setText(tr("Successful Connection"));
        msg.setIcon(QMessageBox::Information);
        msg.exec();

    }
    catch(std::string exc){
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
{
    printerObject->setBedTemp(0);
    for(int i=0;i<extruderQnt;i++)
        printerObject->setExtrTemp(i,0);
    stopThreadRoutine();
    printerObject->~Repetier();
    ui->bt_Bed->setChecked(false);
    ui->bt_extruder0->setChecked(false);
    ui->ManualControlTab->setDisabled(true);
}
void ManualControlWidget::startBed(bool checked){
    if(checked==true)
    {       float tmp = ui->ds_bedTemp->value();
            this->printerObject->setBedTemp(tmp);
    }
    else
    {   ui->bt_Bed->setStyleSheet("");
       this->printerObject->setBedTemp(0);
    }

}
void ManualControlWidget::startExtruders(bool checked){
    if(checked)
    {
        for(int i=1;i<=extrudersInUse;i++)
           this->printerObject->setExtrTemp(i-1,ui->ds_extruderTemp->value());

    }
    else
    {
        ui->bt_extruder0->setStyleSheet("");
        for(int i=1;i<=extrudersInUse;i++)
        {   this->printerObject->setExtrTemp(i-1,0);
            switch (i)
            {
            case 1:
                ui->bt_extruder1->setStyleSheet("");
            break;
            case 2:
                ui->bt_extruder2->setStyleSheet("");
            break;
            case 3:
                ui->bt_extruder3->setStyleSheet("");
            break;
            case 4:
                ui->bt_extruder4->setStyleSheet("");
            break;
            default:
                break;
            }
        }
    }

}
void ManualControlWidget::disableExtrudersButtons(bool checked)
{
    if(sender()==ui->bt_extruder1)
    {
        if(checked)
        {
            ui->bt_extruder2->setEnabled(false);
            ui->bt_extruder3->setEnabled(false);
            ui->bt_extruder4->setEnabled(false);
        }
        else
        {
            ui->bt_extruder2->setEnabled(true);
            ui->bt_extruder3->setEnabled(true);
            ui->bt_extruder4->setEnabled(true);
        }

    }
    if(sender()==ui->bt_extruder2)
    {   if(checked)
        {
            ui->bt_extruder1->setEnabled(false);
            ui->bt_extruder3->setEnabled(false);
            ui->bt_extruder4->setEnabled(false);
        }
        else
        {
            ui->bt_extruder1->setEnabled(true);
            ui->bt_extruder3->setEnabled(true);
            ui->bt_extruder4->setEnabled(true);
        }

    }
    if(sender()==ui->bt_extruder3)
    {    if(checked)
        {
            ui->bt_extruder2->setEnabled(false);
            ui->bt_extruder1->setEnabled(false);
            ui->bt_extruder4->setEnabled(false);
        }
        else
        {
            ui->bt_extruder2->setEnabled(true);
            ui->bt_extruder1->setEnabled(true);
            ui->bt_extruder4->setEnabled(true);
        }

    }
    if(sender()==ui->bt_extruder4)
    {
        if(checked)
        {
            ui->bt_extruder2->setEnabled(false);
            ui->bt_extruder3->setEnabled(false);
            ui->bt_extruder1->setEnabled(false);
        }
        else
        {
            ui->bt_extruder2->setEnabled(true);
            ui->bt_extruder3->setEnabled(true);
            ui->bt_extruder1->setEnabled(true);
        }

    }

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
void ManualControlWidget::updateTemp(double *tempExtruders, double tempBed)
{   //This function update the printer temperatures on the screen
    float temp_Bed = tempBed;
    //Change bed temperatures
    ui->sl_bed->setValue(temp_Bed);
    ui->lb_bedTemp->setText(QVariant(temp_Bed).toString());
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
        ui->lb_extruderTemp0->setText(QVariant(tempExtruders[0]).toString());//Set Label of slider
        ui->lb_extruderTemp1->setText(QVariant(tempExtruders[0]).toString());//Set label on Ext 1
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
                        ui->lb_extruderTemp0->setText(QVariant(tempExtruders[i-1]).toString());//Set Label of slider
                    }
                    //Refresh Color Status
                    if(ui->bt_extruder0->isChecked())
                    {   if(ui->lb_extruderTemp1->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())
                            ui->bt_extruder1->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                    }
                    ui->lb_extruderTemp1->setText(QVariant(tempExtruders[i-1]).toString());//Set label extruder value

                }break;
                case 2:
                {   if(ui->bt_extruder2->isChecked())//Slider belongs to extruder two
                    {   ui->sl_extruder->setValue(tempExtruders[i-1]);
                        ui->lb_extruderTemp0->setText(QVariant(tempExtruders[i-1]).toString());//Set Label of slider
                    }
                   //Refresh Color Status
                   if(ui->bt_extruder0->isChecked())
                   {    if(ui->lb_extruderTemp2->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())//Refresh Color Status
                            ui->bt_extruder2->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder2->setStyleSheet("background-color:yellow;");
                   }
                   ui->lb_extruderTemp2->setText(QVariant(tempExtruders[i-1]).toString());
                }break;
                case 3:
                {  if(ui->bt_extruder3->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(tempExtruders[i-1]);
                       ui->lb_extruderTemp0->setText(QVariant(tempExtruders[i-1]).toString());//Set Label of slider
                   }

                    //Refresh Color Status
                   if(ui->bt_extruder0->isChecked())
                   {
                       if(ui->lb_extruderTemp3->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())//Refresh Color Status
                            ui->bt_extruder3->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder3->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp3->setText(QVariant(tempExtruders[i-1]).toString());
                }break;
                case 4:
                {  if(ui->bt_extruder4->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(tempExtruders[i-1]);
                       ui->lb_extruderTemp0->setText(QVariant(tempExtruders[i-1]).toString());//Set Label of slider
                   }
                   //Change Color Status
                   if(ui->bt_extruder0->isChecked())
                   {
                        if(ui->lb_extruderTemp4->text().toFloat()>=ui->ds_extruderTemp->value() && ui->bt_extruder0->isChecked())//Refresh Color Status
                            ui->bt_extruder4->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder4->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp4->setText(QVariant(tempExtruders[i-1]).toString());
                }break;
                default:
                    break;
                }
            }
}
}
void ManualControlWidget::stopThreadRoutine()
{
    temp->setLoop(true);
    temp->wait(2000);
    temp->quit();
    temp->~ThreadRoutine();
}
void ManualControlWidget::startThreadRoutine()
{
     temp = new ThreadRoutine(printerObject,&extrudersInUse);
     temp->start();
     connect(temp,SIGNAL(updateTemp(double*,double)),this,SLOT(updateTemp(double*,double)));
     connect(temp,SIGNAL(updatePos(double, double, double)), ui->extruderControlWidget, SLOT(updatePos(double, double, double)));

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
//This function locate the Sli3er program and save on Ini file
void ManualControlWidget::locateSlicer()
{   QMessageBox msg;
    garbage=std::system("whereis slic3r > slic3r.txt");
    std::ifstream slicer("slic3r.txt");
    char path[201];
    if(!slicer)
    {
        msg.setText("Bin Slic3r could not be open!");
        msg.exec();
    }
    else
    {   if(!slicer.eof())
        {   slicer.getline(path,sizeof(path));//Lê a linha do arquivo
            if(path[7]=='\0')
            {
               msg.setText("Slic3r not found! To search click on add Slicer on tab Slicer!");
               ui->cb_slicer->addItem("Slic3er (Not Found)");
               //msg.exec();
            }
            else
            {   for(int i=8;path[i]!=' ';i++)
                {
                    pathslicer+=path[i];
                }
                ui->cb_slicer->addItem("Slic3r");
                settings.setValue("slic3r",pathslicer);//Save the path on ini file
                settings.sync();//Atualiza ini
            }
        }
    }
}
//This function locate the Cura program and save on Ini file
void ManualControlWidget::locateCura()
{   QMessageBox msg;
    garbage=std::system("whereis cura > cura.txt");
    std::ifstream cura("cura.txt");
    char path[201];
    if(!cura)
    {
        msg.setText("Bin Cura could not be open!");
        msg.exec();
    }
    else
    {
        if(!cura.eof())
        {
            cura.getline(path,sizeof(path));//read line of the file
            if(path[5]=='\0')
            {
                ui->cb_slicer->addItem("Cura Engine (Not Found)");
            }
            else
            {
                for(int j=6;path[j]!=' ';j++)
                {
                    pathcura+=path[j];
                }
               ui->cb_slicer->addItem("Cura Engine");
               settings.setValue("cura",pathcura);
               settings.sync();
            }
        }
    }
}

void ManualControlWidget::setExtrudersInUse(int e)
{
    extrudersInUse = e;
    hideExtruders(e);
}
void ManualControlWidget::setGcodePreview(QString t){
    ui->GCodePreview->setPlainText(t);
}
void ManualControlWidget::startPrintJob(QString filePath){
   QMessageBox msg;
   stopThreadRoutine();
   try {    std::string path = filePath.toUtf8().constData();
            printerObject->openFile(path,printLogStatus);
            printerObject->startPrintJob(true);
            msg.setText(tr("Print job started!"));
            msg.exec();
            startThreadRoutine();
            emit disablePositionButtons(true);
            connect(temp, SIGNAL(finishedJob(bool)), this, SLOT(isPrintJobRunning(bool)));
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
void ManualControlWidget::isPrintJobRunning(bool b)
{
    //This function return if the print job is finalized
    QMessageBox msg;
    if (b == true) {
        disconnect(temp, SIGNAL(finishedJob(bool)), this, SLOT(isPrintJobRunning(bool)));
        msg.setText("Print job finish or paused!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
        emit disableCbExtruderQnt(true);
        if(!pauseStatus){
            emit disablePositionButtons(false);
            emit disableCbExtruderQnt(false);
        }
    }
}
void ManualControlWidget::pausePrintJob(bool b){
    if (b){
        printerObject->stopPrintJob();
        disconnect(temp, SIGNAL(finishedJob(bool)), this, SLOT(isPrintJobRunning(bool)));
       }
    else{
          printerObject->startPrintJob(false);
          connect(temp, SIGNAL(finishedJob(bool)), this, SLOT(isPrintJobRunning(bool)));
       }
    pauseStatus = b;

}
void ManualControlWidget::stopPrintJob(){
    QMessageBox msg;
    stopThreadRoutine();
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
    startThreadRoutine();
}

void ManualControlWidget::stopOnEmergency(){
    QMessageBox msg;
    stopThreadRoutine();
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

    if(sender()==ui->ds_printSpeed){
        int speed = ui->ds_printSpeed->value();
        printerObject->setFeedRate(speed);
        ui->sl_printSpeed->setValue(speed);
        ui->lb_printSpeed->setText(QString::number(speed));
    }
    if(sender()==ui->ds_filamentFlow){
        int flow = ui->ds_filamentFlow->value();
        printerObject->setFlowRate(flow);
        ui->sl_filamentFlow->setValue(flow);
        ui->lb_filFlowValue->setText(QString::number(flow));

    }
    if(sender()==ui->ds_coolerFan)
    {
        int fan = ui->ds_coolerFan->value();
        printerObject->setFanSpeed(fan);
        ui->sl_coolerFan->setValue(fan);
        ui->lb_coolerValue->setText(QString::number(fan));
    }

}
void ManualControlWidget::setValue(int v){
    if(sender()==ui->sl_printSpeed)
    {
        ui->ds_printSpeed->setValue(v);
        ui->lb_printSpeed->setText(QString::number(v));
        printerObject->setFeedRate(v);
    }
    if(sender()==ui->sl_filamentFlow)
    {
        ui->ds_filamentFlow->setValue(v);
        ui->lb_filFlowValue->setText(QString::number(v));
        printerObject->setFlowRate(v);
    }
    if(sender()==ui->sl_coolerFan)
    {
        ui->ds_coolerFan->setValue(v);
        ui->lb_coolerValue->setText(QString::number(v));
        printerObject->setFanSpeed(v);
    }
}
