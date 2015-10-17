#include "brprint3d.h"
#include "ui_Pandora.h"


BrPrint3D::BrPrint3D(QWidget *parent) : QMainWindow(parent),
ui(new Ui::BrPrint3D)
{
    ui->setupUi(this);

}

BrPrint3D::~BrPrint3D()
{
    delete ui;

}

QSettings settings(QDir::currentPath()+"/br.ini",QSettings::IniFormat); //Arquivo INI


/*******************************************************************************************************************/
/*Organização do Código
 * Função de Inicialização da Pandora
 *
 * --Ações MenuBar--
 *  Sair
 *  Alterar Idioma -> Portugues/Ingles
 *  Sobre -> BrPrint, Documentação, Ajuda, Aviso Legal
 *
 * Função Hide/Show Configurações
 * Funções de Busca
 *  Locate Slicer
 *  Locate Cura
 *  Locate Arduino
 * Funções de Ações sobre Slicer
 *  Iniciar Fatiamento
 *  Cancelar Fatiamento
 * Ações Barra de Menu
 *  Importar GCODE pronto pra impressão
 *  Abrir GCODE ou STL
 *  Conectar/Desconectar Impressora
 * Ação Salvar Configurações
 * Ação estatísticas de impressão
 * Ação Carregar Configurações
 *
 * --Ações com a Impressora--
 * Ações Barra de Menu
 *  Iniciar Impressão
 *  Pausar Impressão
 *  Cancelar Impressão
 *  Parada de Emergência
 * Controle Manual:
 *  Mover X para 0
 *  Mover Y para 0
 *  Mover Z para 0
 *  Mover XYZ para 0
 *  Mover X para Esquerda - largura
 *  Mover X para Direita - largura
 *  Mover Y para Trás -profundidade
 *  Mover Y para Frente -profundidade
 *  Mover Z para Cima -altura
 *  Mover Z para Baixo -altura
 *  Recolher Filamento
 *  Expulsar Filamento 1x
 *  Expulsar Filamento 2x
 *  Set Velocidade de alimentação de filamento
 *  Set Vazão de saída de filamento
 *  Set velocidade do cooler
 *  Ligar/Desligar aquecimento da Mesa
 *  Ligar/Desligar aquecimento do(s) Extrusore(s)
 *
 *--Ações 3D--
 * Renderizar Objeto a partir de um GCODE
 * Renderizar Objeto a partir de um STL
 * Rotacionar Objeto
 * Zoom in/out do Objeto
 * Ter um cubo de impressão nas medidas de área inseridas pelo usuário
 * Renderizar objeto durante impressão
 *
 * --Funções de Conveniencia--
 * Thread de Monitoramento de Temperatura
 * Thread de Monitoramento de Posição do Extrusor
 * Thread de Monitoramento de Conexão de Arduino
 * Função de Liberação de Botões de Extrusores a partir da qnt selecionada
 * Desabilitar botões de movimento de extrusor durante impressão
 * Ação CloseEvent - Verificar se o usuario deseja mesmo fechar o programa
 * Detectar idioma da máquina e carregar pandora com o idioma do sistema
 *

*/

/*-----------Pandora Initialization--------*/
/*This function makes the initialization of the UI.
Loading previously saved settings, locating slicers and Arduino connection.*/
void BrPrint3D::init()
{    Loading *l=new Loading();
     //l->setParent(this,Qt::Window);
     l->show();
    //Init the translator
    this->translator.load(":/Translations/PT_portuguese.qm");
    //Load the previous configs if them exists
    QStringList groups;
    settings.beginGroup("Printer_Configs");
    groups = settings.childGroups();
    settings.endGroup();
    ui->cb_printer->addItems(groups);
    if(!groups.isEmpty())
    {
        QString a = ui->cb_printer->currentText();
        loadConfigs(a);
        //Connection Tab
        ui->cb_Connection_Type->setCurrentText(this->connectionType);
        ui->cb_Transmition_Rate->setCurrentText(this->transmissionRate);
        ui->cb_Firmware->setCurrentText(this->firmwareType);
        ui->cb_Cache_Size->setCurrentText(this->cacheSize);

        //Resets
        ui->ck_resetonConnect->setChecked(this->resetOnConnect);
        ui->ck_resetonEmergency->setChecked(this->resetOnEmergency);
        ui->ck_logImpressao->setChecked(this->printLog);

        //Printer Tab
        ui->tb_RateMoviment->setText(this->rateMoviment);
        ui->tb_FeedZ->setText(this->feedZ);
        ui->tb_ExtruderSpeed_Sec->setText(this->extruderSpeed);
        ui->tb_extruder_vol_max->setText(this->extruderMAXVol);
        ui->tb_SpeedRetraction->setText(this->extruderRetraction);
        ui->tb_Table_Temperature->setText(this->bedTemperature);
        ui->tb_ExtruderTemperature->setText(this->extruderTemperature);
        ui->tb_AreaPrint_X->setText(this->areaX);
        ui->tb_AreaPrint_Y->setText(this->areaY);
        ui->tb_AreaPrint_Z->setText(this->areaZ);

        //Extruder Tab
        ui->cb_Extruder_qnt->setCurrentText(this->extruderQnt);
        ui->tb_extruderMaxTemp->setText(this->extruderMAXTemp);
        ui->tb_bedMaxTemp->setText(this->bedMAXTemp);
        ui->tb_extruder_vol_max->setText(this->extruderMAXVol);
    }

    ui->GCodePreview->setPlainText(tr("Nenhum arquivo carregado."));

    //Set Values on labels of Manual Control
    ui->lb_value_cooler->setText(QVariant (ui->sl_coolerFan->value()).toString());
    ui->lb_bedTemp->setText(QVariant (ui->sl_bed->value()).toString());
    ui->lb_value_speedfil->setText(QVariant (ui->sl_speedFeedFilament->value()).toString());
    ui->lb_value_vazaofil->setText(QVariant (ui->sl_filamentFlow->value()).toString());
    ui->lb_extruderTemp0->setText(QVariant (ui->sl_extruder->value()).toString());

    //ui->bt_hide->setText(tr("Configurações - Mostrar"));

    //Hide Config Menu
    ui->Menu_Control_Left->hide();
    ui->openGLWidget->setGeometry(20,160,900,510);

    //Disable Play Button
    ui->bt_play->setEnabled(false);

    //If slic3er exists in Ini file, load path, else locate
    pathslicer=QVariant (settings.value("slic3r")).toString();
    if(pathslicer.isEmpty())
       locate_Slicer();
    else
    {     ui->cb_Slicer->addItem("Slic3r");
          ui->bt_addSlicer->setEnabled(false);
    }

    //If cura exists in Ini file, load path, else locate
    pathcura=QVariant (settings.value("cura")).toString();
    if(pathcura.isEmpty())
        locate_Cura();
    else
        ui->cb_Slicer->addItem("Cura Engine");

    //Disable Manual Control of Printer
    ui->Manual_Control->setDisabled(true);
    //Disable Slicer Tab - Because is not done
    ui->Slicer->setEnabled(false);

   /* //Start the thread that is listening if Arduino is connect or not
    //this->ard_List = new arduinoListener;
    //connect(ard_List,SIGNAL(arduinoConnect(bool,QString)),this,SLOT(locate_Arduino(bool,QString)));
    //this->ard_List->start();
    QStringList ports;
    ports.append("/dev/ttyACM0");
    ports.append("/dev/ttyUSB0");
    ui->cb_Connection_Port->addItems(ports);*/

}
/*-----------Actions of MenuBar----------*/
//This Action Close the program - Necessary???
void BrPrint3D::on_actionFechar_triggered()
{
    //Do some things -> Is print job running? alert Is something that need to be safe? alert...
}
//This Action change the language of the program to Portuguese
void BrPrint3D::on_actionPortuguese_triggered()
{
    qApp->removeTranslator(&translator);
    translator.load(":/Translations/PT_portuguese.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}
//This Action change the language of the program to English
void BrPrint3D::on_actionEnglish_triggered()
{
   qApp->removeTranslator(&translator);
   translator.load(":/Translations/EN_english.qm");
   qApp->installTranslator(&translator);
   ui->retranslateUi(this);

}
//This action show on screen the Legal Warning Window of BrPrint
void BrPrint3D::on_actionAviso_Legal_triggered()
{
    LegalWarning *w=new LegalWarning();
    w->show();
}
//This action show on screen the Documentation Window of BrPrint
void BrPrint3D::on_actionDocumenta_o_triggered()
{

    Documentation *w= new Documentation();
    w->show();
}
//This action show on screen the Help Window
void BrPrint3D::on_actionAjuda_triggered()
{
    Help *w= new Help();
     w->show();
}
//This action show on screen the about Window of BrPrint
void BrPrint3D::on_actionSobre_o_BrPrint3D_triggered()
{
    aboutBrPrint *w= new aboutBrPrint();
    w->show();
}

/*----------Actions---------------------*/
//This action Hide/Show The Configuration of Printer
void BrPrint3D::on_bt_hide_clicked()
{
    if(ui->bt_hide->text()==tr("Configurações - Mostrar"))
    {
        ui->bt_hide->setText(tr("Configurações - Esconder"));
        ui->Menu_Control_Left->show();
        ui->openGLWidget->setGeometry(460,160,480,510);
    }
    else
    {
        ui->bt_hide->setText(tr("Configurações - Mostrar"));
        ui->Menu_Control_Left->hide();
        ui->openGLWidget->setGeometry(20,160,900,510);
    }
}
//This function locate the Sli3er program and save on Ini file
void BrPrint3D::locate_Slicer()
{   QMessageBox msg;
    garbage=std::system("whereis slic3r > slic3r.txt");
    std::ifstream slicer("slic3r.txt");
    char path[201];
    if(!slicer)
    {

        msg.setText("Arquivo Slic3er não pode ser aberto!");
        msg.exec();
    }
    else
    {   if(!slicer.eof())
        {   slicer.getline(path,sizeof(path));//Lê a linha do arquivo
            if(path[7]=='\0')
            {
               msg.setText("Slic3r nao encontrado, para encontrar manualmente vá na aba Slicer e clique em procurar.");
               ui->cb_Slicer->addItem("Slic3er (Não encontrado)");
            }
            else
            {   for(int i=8;path[i]!=' ';i++)
                {
                    pathslicer+=path[i];
                }
                ui->cb_Slicer->addItem("Slic3r");
                settings.setValue("slic3r",pathslicer);//Salva o path no arquivo ini
                settings.sync();//Atualiza ini
            }
        }
    }
}
//This function locate the Cura program and save on Ini file
void BrPrint3D::locate_Cura()
{   QMessageBox msg;
    garbage=std::system("whereis cura > cura.txt");
    std::ifstream cura("cura.txt");
    char path[201];
    if(!cura)
    {
        msg.setText("Arquivo Slic3er não pode ser aberto!");
    }
    else
    {
        if(!cura.eof())
        {
            cura.getline(path,sizeof(path));//Lê a linha do arquivo
            if(path[5]=='\0')
            {
                ui->cb_Slicer->addItem("Cura Engine (Não instalado)");
            }
            else
            {
                for(int j=6;path[j]!=' ';j++)
                {
                    pathcura+=path[j];
                }
               ui->cb_Slicer->addItem("Cura Engine");
               settings.setValue("cura",pathcura);
               settings.sync();
            }
        }
    }
}
/*//This function locate the port that the arduino is connect
void BrPrint3D::locate_Arduino(bool b,QString word)
{   /*this->ard_List->wait(2000);
    this->ard_List->quit();
    this->ard_List->deleteLater();
    QList<QString> ports;
    garbage=std::system("dmesg | grep -i usb | grep -i tty > usbport.txt");
    QFile usbport("usbport.txt");
    if(usbport.open(QIODevice::ReadOnly|QIODevice::Text))
    {       QTextStream in(&usbport);
            QString file = in.readAll();
             usbport.close();
             QString port,ant=NULL;
               std::string temp = file.toStdString();
               const char *look = temp.c_str();
               qDebug()<<QString(word);
               if(word=="Arduino")
               {
                    look = strstr(look, "Arduino");
                    while(look != NULL)
                    {
                        look = strstr(look, "tty");
                        for(int i = 0; look[i] != ':'; i++)
                            port+=look[i];

                        if(ant!=port)
                        {   ports.append("/dev/"+port);
                            ant=port;
                        }
                        port.clear();
                        look = strstr(look, "Arduino");
                    }
                }
               else
                   ports.append("/dev/ttyUSB0");

    }
    ui->cb_Connection_Port->clear();
    ui->cb_Connection_Port->addItems(ports);


}*/
//This action search for Slic3er manually, if the slic3er isnt installed, the user could user the bin
void BrPrint3D::on_bt_addSlicer_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, "Abrir Arquivo","/home/~","slic3r");
    ui->cb_Slicer->setItemText(0,"Slic3r");
    settings.setValue("slic3r",filename);
    settings.sync();
    ui->bt_addSlicer->setEnabled(false);
}
//This action start the job of slicing
void BrPrint3D::on_bt_startSlicer_clicked()
{
    if(ui->cb_Slicer->currentText()=="Slic3r")
    {

    }
    if(ui->cb_Slicer->currentText()=="Cura Engine")
    {

    }
}
//This action kill the job of slicing
void BrPrint3D::on_bt_killSlicer_clicked()
{

}
//This action import a GCODE file to print
void BrPrint3D::on_bt_import_clicked()
{
    pathGcode=QFileDialog::getOpenFileName(this, "Abrir Arquivo","/home/~","*.gcode");

    if(!pathGcode.isEmpty() && QFileInfo(pathGcode).completeSuffix()=="gcode")
    {   QFile gcode(pathGcode);
        if(gcode.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&gcode);
            QString text = in.readAll();
            readgcode(text);
            gcode.close();
            ui->GCodePreview->setPlainText(text);
            if(ui->bt_connect->isChecked())
                ui->bt_play->setEnabled(true);

        }
    }
}
//This action open a GCODE or STL file
void BrPrint3D::on_bt_open_clicked()
{
    pathGcode=QFileDialog::getOpenFileName(this, "Abrir Arquivo","/home","*.gcode");

    if(!pathGcode.isEmpty() && QFileInfo(pathGcode).completeSuffix()=="gcode")
    {   QFile gcode(pathGcode);
        if(gcode.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&gcode);
            QString text = in.readAll();
            readgcode(text);
            gcode.close();
            ui->GCodePreview->setPlainText(text);
        }
    }
   /* else if(QFileInfo(filename).completeSuffix()=="STL" ||QFileInfo(filename).completeSuffix()=="stl")
    {
        //ui->GCodePreview->setPlainText("");
        //QVector<triangle> QFileInfo(filename).baseName();
        //ERRADO!
       // QFile stl(filename);
        //readstl(filename);
        //Renderiza Imagem
    }*/
}
//This function transform the gcode file on a vector of points and send to OpenGL to draw
void BrPrint3D::readgcode(QString text)
{
    QStringList list = text.split("\n",QString::SkipEmptyParts);


    float x=0,y=0,z=0;
    for(int i=0; i!=list.size(); i++)
    {
        if(list[i].startsWith(";")==false)
        {
            QStringList aux = list[i].split(" ");
            //qDebug() << QStringList(aux) << "\n";
            for(int j=1;j!=aux.size();j++)
            {
                if(aux[j].startsWith("X") && aux[j+1].startsWith("Y"))
                {
                    //ler ponto
                    QString x_str = aux[j].section("X",1);
                     x = x_str.toFloat();
                    QString y_str = aux[j+1].section("Y",1);
                     y = y_str.toFloat();
                      Points *p= new Points();
                      p->addPoint(x,y,z);
                      gcodeDots.append(p);
                }
               else if(aux[j].startsWith("Z"))
                {
                  //ler ponto
                    QString z_str = aux[j].section("Z",1);
                    z = z_str.toFloat();
                    Points *p= new Points();
                    p->addPoint(x,y,z);
                    gcodeDots.append(p);
                }
            }//fim for j
        }
    }//fim for i
  ui->openGLWidget->openGcode(&gcodeDots);
  ui->openGLWidget->update();
}
//This action connect the 3D printer
void BrPrint3D::on_bt_connect_clicked(bool checked)
{  QMessageBox msg;
    int maxX,maxY,maxZ,transmitionRate,bufferSize;
    std::string serialPort;
   if(checked==true)
   {
        if(!ui->tb_AreaPrint_X->text().isEmpty() && !ui->tb_AreaPrint_Y->text().isEmpty() && !ui->tb_AreaPrint_Z->text().isEmpty())
        {
            maxX = ui->tb_AreaPrint_X->text().toInt();
            maxY = ui->tb_AreaPrint_Y->text().toInt();
            maxZ = ui->tb_AreaPrint_Z->text().toInt();
            transmitionRate = ui->cb_Transmition_Rate->currentText().toInt();
            serialPort = ui->cb_Connection_Port->currentText().toStdString();
            bufferSize = ui->cb_Cache_Size->currentText().toInt();
            ui->Manual_Control->setEnabled(true);
        }
        else
        {    msg.setText(tr("Verifique se você fez todas as configurações necessárias da impressora 3D!"));
             msg.setIcon(QMessageBox::Warning);
             msg.exec();
             ui->bt_connect->setChecked(false);
             return;
        }
        if(ui->ck_resetonConnect->isChecked()==true)
             this->resetWhenConnect = true;
        else
             this->resetWhenConnect = false;
        //This check the decimal point valid
        QLocale locale;
        QChar c = locale.decimalPoint();
        if(c=='.')
            this->isCommaDecimalMark = false;
         else
            this->isCommaDecimalMark = true;


        try{
            printer_object = new Repetier(transmitionRate, serialPort, bufferSize, maxX, maxY, maxZ, resetWhenConnect, isCommaDecimalMark);
            int qnt = printer_object->getNoOfExtruders();
            for(int i=0;i<qnt;i++)
            {   QString item = QVariant(i+1).toString();
                ui->cb_Extruder_qnt->addItem(item);
            }
           double x,y,z;
           char resp[51];
           x = this->printer_object->getCurrentXPos();
           y = this->printer_object->getCurrentYPos();
           z = this->printer_object->getCurrentZPos();

           sprintf(resp, "%.3lf", x);
           QString xx = QString::fromUtf8(resp);
           ui->tb_posicaoeixoX->setText(xx);
           sprintf(resp, "%.3lf", y);
           QString yy = QString::fromUtf8(resp);
           ui->tb_posicaoeixoY->setText(yy);
           sprintf(resp, "%.3lf", z);
           QString zz = QString::fromUtf8(resp);
           ui->tb_posicaoeixoZ->setText(zz);
           //Create the tread for read temperatures and position
           this->temp = new ThreadRoutine(this->printer_object,&extrudersInUse);
           this->temp->start();
           //Connect some signals
           connect(temp,SIGNAL(updateTemp(double*,double)),this,SLOT(updateTemp(double*,double)));
           connect(temp,SIGNAL(updateExt(double,double,double)),this,SLOT(updateExt(double,double,double)));
           //Enable button for start printing
           ui->bt_play->setEnabled(true);
           qntextruders = this->printer_object->getNoOfExtruders();
           QStringList l;
           for(int i=1;i<=qntextruders;i++)
           {
               l.append(QVariant(i).toString());
           }
           ui->cb_Extruder_qnt->addItems(l);

           msg.setText(tr("Conexão efetuada com sucesso!"));
           msg.setIcon(QMessageBox::Information);
           msg.exec();
        }
        catch(std::string exc)
        {   QString e =QString::fromUtf8(exc.c_str());
            msg.setText(e);
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
            ui->Manual_Control->setEnabled(false);
            ui->bt_connect->setChecked(false);
        }

     }//fim if check true
     else
     {
       this->printer_object->setBedTemp(0);
       int qnt = this->printer_object->getNoOfExtruders();
       for(int i=0;i<qnt;i++)
       {
           this->printer_object->setExtrTemp(i,0);
       }

       this->temp->setLoop(true);
       this->temp->wait(2000);
       this->temp->quit();
       this->temp->~ThreadRoutine();
       this->printer_object->~Repetier();
       //Check Bed to false
       ui->bt_Bed->setChecked(false);
       ui->bt_Bed->setStyleSheet("");
      //Check extruder to false
       ui->bt_extruderTemp->setChecked(false);
       ui->bt_extruderTemp->setStyleSheet("");


       ui->Manual_Control->setDisabled(true);
     }
}
//This action save the configs insert by the user on Printer Configs in Ini File
void BrPrint3D::on_bt_saveConfig_clicked() //Salva as configurações de impressoras
{   bool ok;
    QString name = QInputDialog::getText(this, tr("Insira nome da configuração: "),tr("Nome:"),QLineEdit::Normal,"ex.: Graber1",&ok);
    settings.beginGroup("Printer_Configs");
    if(ok && !name.isEmpty())
    {
        settings.beginGroup(name);
        //Conexao
        settings.setValue("Firmware",ui->cb_Firmware->currentText());
        settings.setValue("ResetOnConnect",ui->ck_resetonConnect->checkState());
        settings.setValue("ResetonEmergency",ui->ck_resetonEmergency->checkState());
        settings.setValue("CacheSize", ui->cb_Cache_Size->currentText());
        settings.setValue("TransmissionRate",ui->cb_Transmition_Rate->currentText());
        settings.setValue("PrinterLog", ui->ck_logImpressao->checkState());
        //Impressora
        settings.setValue("RateMoviment",ui->tb_RateMoviment->text());
        settings.setValue("FeedZ",ui->tb_FeedZ->text());
        settings.setValue("ExtruderSpeed",ui->tb_ExtruderSpeed_Sec->text());
        settings.setValue("ExtruderRetraction",ui->tb_SpeedRetraction->text());
        settings.setValue("BedTemperature",ui->tb_Table_Temperature->text());
        settings.setValue("ExtruderTemperature",ui->tb_ExtruderTemperature->text());
        settings.setValue("AreaX",ui->tb_AreaPrint_X->text());
        settings.setValue("AreaY",ui->tb_AreaPrint_Y->text());
        settings.setValue("AreaZ",ui->tb_AreaPrint_Z->text());
        //Extrusor
        settings.setValue("ExtruderQnt",ui->cb_Extruder_qnt->currentText());
        settings.setValue("ExtruderMaxTemp",ui->tb_extruderMaxTemp->text());
        settings.setValue("BedMaxTemp",ui->tb_bedMaxTemp->text());
        settings.setValue("VolumeMax",ui->tb_extruder_vol_max->text());
        settings.endGroup();

    }
    settings.endGroup();
    QStringList groups;
    settings.beginGroup("Printer_Configs");
    groups = settings.childGroups();
    settings.endGroup();
    ui->cb_printer->clear();
    ui->cb_printer->addItems(groups);
}
//This actions loads the config choose by the user on Printer Configs
void BrPrint3D::on_cb_printer_currentTextChanged(const QString &arg1)
{
    loadConfigs(arg1);
}
void BrPrint3D::loadConfigs(QString q)
{
        settings.beginGroup("Printer_Configs");
        settings.beginGroup(q);
        //Connection
        this->connectionType = settings.value("ConnectionType","USB").toString();
        this->transmissionRate = settings.value("TransmissionRate","115200").toString();
        this->firmwareType = settings.value("Firmware","Repetier").toString();
        this->cacheSize = settings.value("CacheSize","127").toString();
        this->resetOnConnect = settings.value("ResetOnConnect",2).toInt();
        this->resetOnEmergency = settings.value("ResetonEmergency",0).toInt();
        this->printLog = settings.value("PrinterLog",0).toInt();

        //Printer
        this->rateMoviment = settings.value("RateMoviment",0).toString();
        this->feedZ = settings.value("FeedZ",0).toString();
        this->extruderSpeed = settings.value("ExtruderSpeed",0).toString();
        this->extruderRetraction = settings.value("ExtruderRetraction",0).toString();
        this->extruderTemperature = settings.value("ExtruderTemperature",210).toString();
        this->bedTemperature = settings.value("BedTemperature",110).toString();
        this->areaX = settings.value("AreaX",0).toString();
        this->areaY = settings.value("AreaY",0).toString();
        this->areaZ = settings.value("AreaZ",0).toString();

        //Extruder
        this->extruderQnt = settings.value("ExtruderQnt",1).toString();
        this->extruderMAXTemp = settings.value("ExtruderMaxTemp",230).toString();
        this->bedMAXTemp = settings.value("BedMaxTemp",120).toString();
        this->extruderMAXVol = settings.value("VolumeMax",0).toString();
        settings.endGroup();
        settings.endGroup();

}

/*-----------Printer Actions-----------*/
//This actions start the printer job
void BrPrint3D::on_bt_play_clicked()
{     QMessageBox msg;
     if(!pathGcode.isEmpty())
     {  //destroy the thread
         this->temp->setLoop(true);
         this->temp->wait(2000);
         this->temp->quit();
         this->temp->~ThreadRoutine();
         try
         {
            std::string path = pathGcode.toUtf8().constData();
            this->printer_object->openFile(path,ui->ck_logImpressao->isChecked());

          }
         catch(std::string exc)
         {
             QMessageBox msg;
             msg.setIcon(QMessageBox::Critical);
             QString str = QString::fromUtf8(exc.c_str());
             msg.setText(str);
             msg.exec();

         }
         ui->bt_play->setEnabled(false);
         ui->bt_pause->setEnabled(true);
         ui->bt_stop->setEnabled(true);
         this->printer_object->startPrintJob(true);
         msg.setText(tr("Trabalho de impressão Iniciado!"));
         msg.exec();
         //Create a new thread and connect some signals
        temp = new ThreadRoutine(this->printer_object,&extrudersInUse);
         this->temp->start();

         connect(temp,SIGNAL(updateTemp(double*,double)),this,SLOT(updateTemp(double*,double)));
         connect(temp,SIGNAL(updateExt(double,double,double)),this,SLOT(updateExt(double,double,double)));
         connect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));

         //Disable some buttons - to safety
         disableAxisButtons();
         ui->cb_Extruder_qnt->setEnabled(false);
     }
}
//Pensar melhor aqui, por causa do dialog box finalizado/pausado
//This action pause the print job
void BrPrint3D::on_bt_pause_clicked(bool checked)
{
    if(checked==true)
    {     this->printer_object->stopPrintJob();
          disconnect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));
    }
    else
    {   this->printer_object->startPrintJob(false);
        connect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));
    }

}
//This action stop the print job
void BrPrint3D::on_bt_stop_clicked()
{
    ui->bt_play->setEnabled(true);
    ui->bt_pause->setEnabled(false);
    ui->bt_stop->setEnabled(false);
    this->printer_object->stopPrintJob();
    this->printer_object->closeFile();
    this->printer_object->setBedTemp(0);
    for(int i=1;i<=this->extrudersInUse;i++)
        this->printer_object->setExtrTemp(i,0);
    enableAxisButtons();
}
//This action stop print job in emergency case
void BrPrint3D::on_bt_emergency_clicked()
{   QMessageBox msg;
    try
    {
      this->temp->setLoop(true);
       this->temp->wait(2000);
       this->temp->quit();
       this->temp->~ThreadRoutine();

       msg.setText("Parada de Emergência Selecionada, clique em OK e aguarde.");
       msg.setIcon(QMessageBox::Critical);
       msg.exec();
       this->printer_object->scramPrinter();
       msg.setText("Parada de Emergência efetuada com sucesso!");
       msg.setIcon(QMessageBox::Critical);
       msg.exec();
       this->printer_object->~Repetier();
       ui->bt_connect->setChecked(false);
       enableAxisButtons();

    }
    catch(std::string exc)
    {
        QString str = QString::fromUtf8(exc.c_str());
        msg.setText(str);
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }
}

/*-----------Printer Actions - Manual Control----*/
/*Home Extruder Functions*/
//This action set Home X Axis
void BrPrint3D::on_bt_home_X_clicked()
{
    this->printer_object->homeAxis('X');

}
//This action set Home Y Axis
void BrPrint3D::on_bt_home_Y_clicked()
{
    this->printer_object->homeAxis('Y');

}
//This action set home Z Axis
void BrPrint3D::on_bt_home_Z_clicked()
{
    this->printer_object->homeAxis('Z');

}
//This action set home XYZ Axis
void BrPrint3D::on_bt_home_XYZ_clicked()
{
    this->printer_object->homeAllAxis();

}
/*Filament Retract*/
//This action retract the filament
void BrPrint3D::on_bt_filamentoRetract_clicked()
{
    //this->printer_object->extruderControl(0.1,0.1);
}
//This action expulse the filament at 1x
void BrPrint3D::on_bt_filamentoOneSpeed_clicked()
{


}
//This action expulse the filament at 2x
void BrPrint3D::on_bt_filamentoTwoSpeed_clicked()
{


}

/*Sliders Values Set*/
//This action set the value of velocity of feed of filament to slider and printer
void BrPrint3D::on_tb_speedFeedFilament_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of filament Flow to slider and printer
void BrPrint3D::on_tb_filamentFlow_textChanged(const QString &arg1)
{
    ui->sl_speedFeedFilament->setValue(arg1.toInt());
}
//This action set the value of cooler fan to slider and printer
void BrPrint3D::on_tb_coolerfan_textChanged(const QString &arg1)
{
    ui->sl_coolerFan->setValue(arg1.toInt());
}

/*Heating actions*/
//This action start heating the bed of the printer
void BrPrint3D::on_bt_Bed_clicked(bool checked)
{
    if(checked==true)
    {       float tmp = ui->tb_BedTempMC->text().toFloat();
            ui->bt_Bed->setStyleSheet("background-color:yellow;");
            this->printer_object->setBedTemp(tmp);
    }
    else
    {   ui->bt_Bed->setStyleSheet("");
       this->printer_object->setBedTemp(0);
    }
}
//This action start heating the extruder(s)
void BrPrint3D::on_bt_extruderTemp_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruderTemp->setStyleSheet("background-color:yellow;");
        ui->bt_extruder1->setChecked(true);

        for(int i=1;i<=extrudersInUse;i++)
        {
           this->printer_object->setExtrTemp(i-1,ui->tb_ExtruderTempMC->text().toFloat());
            switch (i)
            {
            case 1:
                ui->bt_extruder1->setStyleSheet("background-color:yellow;");
            break;
            case 2:
                ui->bt_extruder2->setStyleSheet("background-color:yellow;");
            break;
            case 3:
               ui->bt_extruder3->setStyleSheet("background-color:yellow;");
            break;
            case 4:
                ui->bt_extruder4->setStyleSheet("background-color:yellow;");
            break;
            default:
                break;
            }
        }
    }
    if(checked==false)
    {
        ui->bt_extruderTemp->setStyleSheet("");
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

/*------------Other Functions--------*/
//This slot update on UI the value of Temperatures of the Bed and Extruders
void BrPrint3D::updateTemp(double *temp_Extruders, double tempBed)
{//This function update the printer temperatures on the screen
    float temp_Bed = tempBed;
      //Change bed temperatures
      ui->sl_bed->setValue(temp_Bed);
      ui->lb_bedTemp->setText(QVariant(temp_Bed).toString());
      if(ui->bt_Bed->isChecked())
      {
           if(ui->sl_bed->value()>=ui->tb_BedTempMC->text().toInt())
               ui->bt_Bed->setStyleSheet("background-color:red;");
           else
               ui->bt_Bed->setStyleSheet("background-color:yellow;");
      }

    //Change extruders temp
        for(int i=0;i<extrudersInUse;i++)
            {
               switch (i)
               {
                case 0:
                {  if(ui->bt_extruder1->isChecked())//Slider belongs to extruder 1
                   {
                        ui->sl_extruder->setValue(temp_Extruders[i]); //Set Slider value
                        ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i]).toString());//Set Label of slider
                   }
                    ui->lb_extruderTemp_1->setText(QVariant(temp_Extruders[i]).toString());//Set label extruder value

                    //Refresh Color Status
                    if(ui->lb_extruderTemp_1->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt())
                        ui->bt_extruder1->setStyleSheet("background-color:red;");
                    else
                        ui->bt_extruder1->setStyleSheet("background-color:yellow;");
                    //If the printer is using one extruder, the slider will belongs all the time to extruder 1
                    if(extrudersInUse==1)
                    {    ui->sl_extruder->setValue(temp_Extruders[i]);
                       ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i]).toString());//Set Label of slider

                    }
                }break;
                case 1:
                {   if(ui->bt_extruder2->isChecked())//Slider belongs to extruder two
                    {   ui->sl_extruder->setValue(temp_Extruders[i]);
                        ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i]).toString());//Set Label of slider
                    }

                   if(ui->lb_extruderTemp_2->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt())//Refresh Color Status
                        ui->bt_extruder2->setStyleSheet("background-color:red;");
                    else
                        ui->bt_extruder2->setStyleSheet("background-color:yellow;");

                    ui->lb_extruderTemp_2->setText(QVariant(temp_Extruders[i]).toString());
                }break;
                case 2:
                {  if(ui->bt_extruder3->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(temp_Extruders[i]);
                       ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i]).toString());//Set Label of slider
                   }


                   if(ui->lb_extruderTemp_3->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt())//Refresh Color Status
                        ui->bt_extruder3->setStyleSheet("background-color:red;");
                    else
                        ui->bt_extruder3->setStyleSheet("background-color:yellow;");

                    ui->lb_extruderTemp_3->setText(QVariant(temp_Extruders[i]).toString());
                }break;
                case 3:
                {  if(ui->bt_extruder4->isChecked())//Slider belongs to extruder two
                   {   ui->sl_extruder->setValue(temp_Extruders[i]);
                       ui->lb_extruderTemp0->setText(QVariant(temp_Extruders[i]).toString());//Set Label of slider
                   }
                   if(ui->lb_extruderTemp_4->text().toFloat()>=ui->tb_ExtruderTempMC->text().toInt())//Refresh Color Status
                        ui->bt_extruder4->setStyleSheet("background-color:red;");
                    else
                        ui->bt_extruder4->setStyleSheet("background-color:yellow;");

                    ui->lb_extruderTemp_4->setText(QVariant(temp_Extruders[i]).toString());
                }break;
                default:
                    break;
                }
            }
}
//This slot update on UI the position of the Extruder
void BrPrint3D::updateExt(double posX, double posY, double posZ)
{   //This function update the extruder position on the screen
    char resp[51];
    sprintf(resp, "%.3lf", posX);
    QString xx = QString::fromUtf8(resp);
    sprintf(resp, "%.3lf", posY);
    QString yy = QString::fromUtf8(resp);
    sprintf(resp, "%.3lf", posZ);
    QString zz = QString::fromUtf8(resp);
    ui->tb_posicaoeixoX->setText(xx);
    ui->tb_posicaoeixoY->setText(yy);
    ui->tb_posicaoeixoZ->setText(zz);

}
//This slot inform the user that the print job is end
void BrPrint3D::isPrintJobRunning(bool b)
{   //This function return if the print job is finalized
    QMessageBox msg;
    if(b==true)
    {   disconnect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));
        msg.setText("Trabalho de impressao finalizado/pausado!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
        if(ui->bt_pause->isChecked()==false)
        {    enableAxisButtons();
            ui->cb_Extruder_qnt->setEnabled(true);
        }
    }
}
//This is a close event
void BrPrint3D::closeEvent(QCloseEvent *event)
{
    QMessageBox msg;
        if(this->printer_object->isPrintJobRunning()==true)
        {   msg.setText("A impressora está em uso, tem certeza que deseja fechar o programa?");
            msg.setIcon(QMessageBox::Warning);
            msg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Cancel);
            int result = msg.exec();
            switch (result)
            {

            case QMessageBox::Cancel:
                event->accept();
                break;
            case QMessageBox::Ok:
            {
                this->printer_object->stopPrintJob();
                this->printer_object->closeFile();
                event->accept();
            }break;
            default:
                break;
            }

        }
        event->accept();
}
//This Action hide/show buttons of extruders starting from qnt choose by the user
void BrPrint3D::on_cb_Extruder_qnt_currentTextChanged(const QString &arg1)
{   this->extrudersInUse = arg1.toInt();
    switch (extrudersInUse)
    {
    case 1:
    {
        ui->bt_extruder2->hide();
        ui->lb_extruderTemp_2->hide();
        ui->lbC2->hide();

        ui->bt_extruder3->hide();
        ui->lb_extruderTemp_3->hide();
        ui->lbC3->hide();

        ui->bt_extruder4->hide();
        ui->lb_extruderTemp_4->hide();
        ui->lbC4->hide();
    }break;
    case 2:
    {   ui->bt_extruder3->hide();
        ui->lb_extruderTemp_3->hide();
        ui->lbC3->hide();

        ui->bt_extruder4->hide();
        ui->lb_extruderTemp_4->hide();
        ui->lbC4->hide();

    }break;
    case 3:
    {
        ui->bt_extruder4->hide();
        ui->lb_extruderTemp_4->hide();
        ui->lbC4->hide();
    }break;

    default:
        break;
    }
}
//This function disable some buttons from Manual Control for safety
void BrPrint3D::disableAxisButtons()
{
    ui->bt_home_X->setEnabled(false);
    ui->bt_home_Y->setEnabled(false);
    ui->bt_home_Z->setEnabled(false);
    ui->bt_home_XYZ->setEnabled(false);
    ui->bt_up_Y->setEnabled(false);
    ui->bt_down_Y->setEnabled(false);
    ui->bt_left_X->setEnabled(false);
    ui->bt_right_X->setEnabled(false);
    ui->bt_down_Z->setEnabled(false);
    ui->bt_up_Z->setEnabled(false);
    ui->bt_filamentoOneSpeed->setEnabled(false);
    ui->bt_filamentoRetract->setEnabled(false);
    ui->bt_filamentoTwoSpeed->setEnabled(false);
}
//This function enable some buttons from Manual Control
void BrPrint3D::enableAxisButtons()
{
    ui->bt_home_X->setEnabled(true);
    ui->bt_home_Y->setEnabled(true);
    ui->bt_home_Z->setEnabled(true);
    ui->bt_home_XYZ->setEnabled(true);
    ui->bt_up_Y->setEnabled(true);
    ui->bt_down_Y->setEnabled(true);
    ui->bt_left_X->setEnabled(true);
    ui->bt_right_X->setEnabled(true);
    ui->bt_down_Z->setEnabled(true);
    ui->bt_up_Z->setEnabled(true);
    ui->bt_filamentoOneSpeed->setEnabled(true);
    ui->bt_filamentoRetract->setEnabled(true);
    ui->bt_filamentoTwoSpeed->setEnabled(true);
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 1
void BrPrint3D::on_bt_extruder1_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder2->setEnabled(false);
        ui->bt_extruder3->setEnabled(false);
        ui->bt_extruder4->setEnabled(false);
        ui->bt_extruderTemp->setText("1");
    }
    else
    {
        ui->bt_extruder2->setEnabled(true);
        ui->bt_extruder3->setEnabled(true);
        ui->bt_extruder4->setEnabled(true);
    }
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 2
void BrPrint3D::on_bt_extruder2_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder1->setEnabled(false);
        ui->bt_extruder3->setEnabled(false);
        ui->bt_extruder4->setEnabled(false);
        ui->bt_extruderTemp->setText("2");
    }
    else
    {
        ui->bt_extruder1->setEnabled(true);
        ui->bt_extruder3->setEnabled(true);
        ui->bt_extruder4->setEnabled(true);
    }
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 3
void BrPrint3D::on_bt_extruder3_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder2->setEnabled(false);
        ui->bt_extruder1->setEnabled(false);
        ui->bt_extruder4->setEnabled(false);
        ui->bt_extruderTemp->setText("3");
    }
    else
    {
        ui->bt_extruder2->setEnabled(true);
        ui->bt_extruder1->setEnabled(true);
        ui->bt_extruder4->setEnabled(true);
    }
}
//This function blocks other buttons for security and ensuring that the slider of extruder temperature is belonging to extruder 4
void BrPrint3D::on_bt_extruder4_clicked(bool checked)
{
    if(checked==true)
    {
        ui->bt_extruder2->setEnabled(false);
        ui->bt_extruder3->setEnabled(false);
        ui->bt_extruder1->setEnabled(false);
        ui->bt_extruderTemp->setText("4");
    }
    else
    {
        ui->bt_extruder2->setEnabled(true);
        ui->bt_extruder3->setEnabled(true);
        ui->bt_extruder1->setEnabled(true);
    }
}
//This Action update the temperature of the bed if the print job is on
void BrPrint3D::on_tb_BedTempMC_textEdited(const QString &arg1)
{   if(ui->bt_play->isChecked() && ui->bt_Bed->isChecked())
        this->printer_object->setBedTemp(arg1.toInt());
}
//This Action update the temperature of the extruders if the print job is on
void BrPrint3D::on_tb_ExtruderTempMC_textEdited(const QString &arg1)
{   if(ui->bt_play->isChecked() && ui->bt_extruderTemp->isChecked() )
    for(int i=1;i<=extrudersInUse;i++)
        this->printer_object->setExtrTemp(i-1,arg1.toInt());
}
//This Action set the X axis to new position on right
void BrPrint3D::on_bt_right_X_clicked()
{   double pos = this->printer_object->getCurrentXPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('X',pos);
}
//This Action set the X axis to new position on left
void BrPrint3D::on_bt_left_X_clicked()
{   QMessageBox msg;
    msg.setText("Posição inválida!");
    msg.setIcon(QMessageBox::Warning);
    double pos = this->printer_object->getCurrentXPos();
    pos-=ui->cb_valuePosXY->currentText().toFloat();
    if(pos<=0)
        msg.exec();
    else
        this->printer_object->moveAxisToPos('X',pos);
}
//This Action set the Y axis to new position on up
void BrPrint3D::on_bt_up_Y_clicked()
{
    double pos = this->printer_object->getCurrentYPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('Y',pos);
}
//This Action set the Y axis to new position on down
void BrPrint3D::on_bt_down_Y_clicked()
{   QMessageBox msg;
    msg.setText("Posição inválida!");
    msg.setIcon(QMessageBox::Warning);
    double pos = this->printer_object->getCurrentYPos();
    pos-=ui->cb_valuePosXY->currentText().toFloat();
    if(pos<=0)
        msg.exec();
    else
        this->printer_object->moveAxisToPos('Y',pos);

}
//This Action set the Z axis to new position on up
void BrPrint3D::on_bt_up_Z_clicked()
{
    double pos = this->printer_object->getCurrentZPos();
    pos+=ui->cb_valuePosXY->currentText().toFloat();
    this->printer_object->moveAxisToPos('Z',pos);

}
//This Action set the Z axis to new position on down
void BrPrint3D::on_bt_down_Z_clicked()
{   QMessageBox msg;
    msg.setText("Posição inválida!");
    msg.setIcon(QMessageBox::Warning);
    double pos = this->printer_object->getCurrentZPos();
    pos-=ui->cb_valuePosXY->currentText().toFloat();
    if(pos<=0)
        msg.exec();
    else
        this->printer_object->moveAxisToPos('Z',pos);
}
