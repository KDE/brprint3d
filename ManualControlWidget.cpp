#include "ManualControlWidget.h"
#include "ui_ManualControlWidget.h"

ManualControlWidget::ManualControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualControlWidget)
{
    ui->setupUi(this);
}

ManualControlWidget::~ManualControlWidget()
{
    delete ui;
}

void ManualControlWidget::init()
{   ui->ManualControlTab->setDisabled(true);
    ui->Slicer->setDisabled(true);
    ui->GCodePreview->setPlainText(tr("No Open File."));
    ExtruderControlWidget *extruderControl = new ExtruderControlWidget;
    ui->ly_ExtruderConteiner->addWidget(extruderControl);

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
/*//This action start the job of slicing
void ManualControlWidget::on_bt_startSlicer_clicked()
{

}
//This action kill the job of slicing
void ManualControlWidget::on_bt_killSlicer_clicked()
{

}
//This action search for Slic3er manually, if the slic3er isnt installed, the user could user the bin
void ManualControlWidget::on_bt_addSlicer_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, "Open File",QDir::homePath(),"slic3r");
    ui->cb_slicer->setItemText(0,"Slic3r");
    settings.setValue("slic3r",filename);
    settings.sync();
    ui->bt_addSlicer->setEnabled(false);
}


/*-----------Printer Actions - Manual Control----*/
/*Home Extruder Functions
//This action set Home X Axis
void ManualControlWidget::on_bt_home_X_clicked()
{
    this->printer_object->homeAxis('X');

}
//This action set Home Y Axis
void ManualControlWidget::on_bt_home_Y_clicked()
{
    this->printer_object->homeAxis('Y');

}
//This action set home Z Axis
void ManualControlWidget::on_bt_home_Z_clicked()
{
    this->printer_object->homeAxis('Z');

}
//This action set home XYZ Axis
void ManualControlWidget::on_bt_home_XYZ_clicked()
{
    this->printer_object->homeAllAxis();

}
/*Filament Retract
//This action retract the filament
void ManualControlWidget::on_bt_filamentoRetract_clicked()
{
    //this->printer_object->extruderControl(0.1,0.1);
}
//This action expulse the filament at 1x
void ManualControlWidget::on_bt_filamentoOneSpeed_clicked()
{


}
//This action expulse the filament at 2x
void ManualControlWidget::on_bt_filamentoTwoSpeed_clicked()
{


}

/*Sliders Values Set
//This action set the value of velocity of feed of filament to slider and printer
void ManualControlWidget::on_tb_speedFeedFilament_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of filament Flow to slider and printer
void ManualControlWidget::on_tb_filamentFlow_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of cooler fan to slider and printer
void ManualControlWidget::on_tb_coolerfan_textChanged(const QString &arg1)
{
    ui->sl_coolerFan->setValue(arg1.toInt());
}

/*Heating actions
//This action start heating the bed of the printer
void ManualControlWidget::on_bt_Bed_clicked(bool checked)
{
    if(checked==true)
    {       float tmp = ui->tb_BedTempMC->text().toFloat();
            this->printer_object->setBedTemp(tmp);
    }
    else
    {   ui->bt_Bed->setStyleSheet("");
       this->printer_object->setBedTemp(0);
    }
}
//This action start heating the extruder(s)
void ManualControlWidget::on_bt_extruderTemp_clicked(bool checked)
{
    if(checked==true)
    {
        for(int i=1;i<=extrudersInUse;i++)
           this->printer_object->setExtrTemp(i-1,ui->tb_ExtruderTempMC->text().toFloat());

    }
    if(checked==false)
    {
        ui->bt_extruderTemp0->setStyleSheet("");
        for(int i=1;i<=extrudersInUse;i++)
        {   this->printer_object->setExtrTemp(i-1,0);
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

//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 1
void ManualControlWidget::on_bt_extruder1_clicked(bool checked)
{
    if(checked==true)
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
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 2
void ManualControlWidget::on_bt_extruder2_clicked(bool checked)
{
    if(checked==true)
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
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 3
void ManualControlWidget::on_bt_extruder3_clicked(bool checked)
{
    if(checked==true)
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
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 4
void ManualControlWidget::on_bt_extruder4_clicked(bool checked)
{
    if(checked==true)
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
//This Action update the temperature of the bed if the print job is on
void ManualControlWidget::on_tb_BedTempMC_textEdited(const QString &arg1)
{   if(playStatus==true && ui->bt_Bed->isChecked())
        this->printer_object->setBedTemp(arg1.toInt());
}
//This Action update the temperature of the extruders if the print job is on
void ManualControlWidget::on_tb_ExtruderTempMC_textEdited(const QString &arg1)
{   if(playStatus==true && ui->bt_extruderTemp0->isChecked() )
    for(int i=1;i<=extrudersInUse;i++)
        this->printer_object->setExtrTemp(i-1,arg1.toInt());
}

void ManualControlWidget::getPrinterObject(Repetier *printer_object)
{
    this->printer_object = printer_object;
}
void ManualControlWidget::setInitialMarks()
{
    this->qntExtruders = this->printer_object->getNoOfExtruders();

    //Add initial position of the extruder
   //Create the tread for read temperatures and position
   this->temp = new ThreadRoutine(this->printer_object,&extrudersInUse);
   this->temp->start();
   //Connect some signals
   connect(temp,SIGNAL(updateTemp(double*,double)),this,SLOT(updateTemp(double*,double)));
}

//This slot update on UI the value of Temperatures of the Bed and Extruders
//There some inconsistency on the tests here - CHECK!
void ManualControlWidget::updateTemp(double *temp_Extruders, double tempBed)
{   //This function update the printer temperatures on the screen
    float temp_Bed = tempBed;
    //Change bed temperatures
    ui->sl_bed->setValue(temp_Bed);
    ui->lb_bedTemp->setText(QVariant(temp_Bed).toString());
    //Update Color Status
    if(ui->bt_Bed->isChecked())
    {
        if(ui->sl_bed->value()>=ui->tb_BedTempMC->text().toInt())
            ui->bt_Bed->setStyleSheet("background-color:red;");
        else
            ui->bt_Bed->setStyleSheet("background-color:yellow;");
     }
     //If the printer is using one extruder, the slider will belongs all the time to extruder 1
     if(extrudersInUse==1)
     {
        ui->sl_extruder->setValue(temp_Extruders[0]);//Set temperature on slider
        ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[0]).toString());//Set Label of slider
        ui->lb_extruderTemp1->setText(QVariant(temp_Extruders[0]).toString());//Set label on Ext 1
        //Change color status
        if(ui->bt_extruderTemp0->isChecked())
        {   if(ui->lb_extruderTemp1->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt())
            {    ui->bt_extruder1->setStyleSheet("background-color:red;");
                 ui->bt_extruderTemp0->setStyleSheet("background-color:red;");
            }
            else
            {    ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                 ui->bt_extruderTemp0->setStyleSheet("background-color:yellow;");
            }
        }

     }
     else
     {  //Change extruders temp
        ui->bt_extruderTemp0->setStyleSheet("background-color:green;");
        for(int i=1;i<=extrudersInUse;i++)
        {
            switch (i)
            {
                case 1:
                {   if(ui->bt_extruder1->isChecked())//Slider belongs to extruder 1
                    {
                        ui->sl_extruder->setValue(temp_Extruders[i-1]); //Set Slider value
                        ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                    }
                    //Refresh Color Status
                    if(ui->bt_extruderTemp0->isChecked())
                    {   if(ui->lb_extruderTemp1->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp0->isChecked())
                            ui->bt_extruder1->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                    }
                    ui->lb_extruderTemp1->setText(QVariant(temp_Extruders[i-1]).toString());//Set label extruder value

                }break;
                case 2:
                {   if(ui->bt_extruder2->isChecked())//Slider belongs to extruder two
                    {   ui->sl_extruder->setValue(temp_Extruders[i-1]);
                        ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                    }
                   //Refresh Color Status
                   if(ui->bt_extruderTemp0->isChecked())
                   {    if(ui->lb_extruderTemp2->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp0->isChecked())//Refresh Color Status
                            ui->bt_extruder2->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder2->setStyleSheet("background-color:yellow;");
                   }
                   ui->lb_extruderTemp2->setText(QVariant(temp_Extruders[i-1]).toString());
                }break;
                case 3:
                {  if(ui->bt_extruder3->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(temp_Extruders[i-1]);
                       ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                   }

                    //Refresh Color Status
                   if(ui->bt_extruderTemp0->isChecked())
                   {
                       if(ui->lb_extruderTemp3->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp0->isChecked())//Refresh Color Status
                            ui->bt_extruder3->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder3->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp3->setText(QVariant(temp_Extruders[i-1]).toString());
                }break;
                case 4:
                {  if(ui->bt_extruder4->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(temp_Extruders[i-1]);
                       ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i-1]).toString());//Set Label of slider
                   }
                   //Change Color Status
                   if(ui->bt_extruderTemp0->isChecked())
                   {
                        if(ui->lb_extruderTemp4->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt() && ui->bt_extruderTemp0->isChecked())//Refresh Color Status
                            ui->bt_extruder4->setStyleSheet("background-color:red;");
                        else
                            ui->bt_extruder4->setStyleSheet("background-color:yellow;");
                   }
                    ui->lb_extruderTemp4->setText(QVariant(temp_Extruders[i-1]).toString());
                }break;
                default:
                    break;
                }
            }
}
}

void ManualControlWidget::stopThreadRoutine()
{
    this->temp->setLoop(true);
    this->temp->wait(2000);
    this->temp->quit();
    this->temp->~ThreadRoutine();
}
void ManualControlWidget::startThreadRoutine()
{
     temp = new ThreadRoutine(this->printer_object,&extrudersInUse);
     this->temp->start();
     connect(temp,SIGNAL(updateTemp(double*,double)),this,SLOT(updateTemp(double*,double)));

}

void ManualControlWidget::setBedStatus(bool b)
{
    ui->bt_Bed->setChecked(b);
    if(b==false)
        ui->bt_Bed->setStyleSheet("");

}
void ManualControlWidget::setExtruderStatus(bool b)
{
    ui->bt_extruderTemp0->setChecked(b);
    if(b==false)
        ui->bt_extruderTemp0->setStyleSheet("");
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
*/
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
/*
void ManualControlWidget::setGcodePreview(QString t)
{
    ui->GCodePreview->setPlainText(t);
}


void ManualControlWidget::_extrudersInUse(int e)
{
    this->extrudersInUse = e;
}
void ManualControlWidget::btPlayStatus(bool b)
{
    playStatus = b;
}
void ManualControlWidget::disableManualControlTb(bool b)
{
    ui->ManualControlTab->setDisabled(b);
}
*/