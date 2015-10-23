#ifndef BRPRINT3D_H
#define BRPRINT3D_H
#include <QMainWindow>
#include <Windows/loading.h>
#include <Windows/documentation.h>
#include <Windows/aboutbrprint.h>
#include <Windows/help.h>
#include <Windows/legalwarning.h>
#include <Windows/loading.h>
#include "points.h"
#include "KI/Repetier.h"
#include "threadRotine.h"
#include "arduinolistener.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <QTranslator>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QVariant>
#include <QSettings>
#include <QObject>
#include <QList>
#include <QInputDialog>
#include <QList>
#include <QStandardPaths>

namespace Ui {
class BrPrint3D;
}

class BrPrint3D : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrPrint3D(QWidget *parent = 0);
    ~BrPrint3D();
    void init();
    void readstl(QString file);
    void renderGcode(QString str);
    void readgcode(QString text);

private slots:
    void locate_Arduino(bool b);
    void on_bt_hide_clicked();
    void on_actionPortuguese_triggered();
    void on_actionFechar_triggered();
    void on_actionAviso_Legal_triggered();
    void on_actionDocumenta_o_triggered();
    void on_actionAjuda_triggered();
    void on_actionSobre_o_BrPrint3D_triggered();
    void on_bt_home_X_clicked();
    void on_bt_home_Y_clicked();
    void on_bt_home_Z_clicked();
    void on_bt_home_XYZ_clicked();
    void on_bt_startSlicer_clicked();
    void on_bt_killSlicer_clicked();
    void on_bt_extruderTemp_clicked(bool checked);
    void on_bt_import_clicked();
    void on_bt_open_clicked();
    void on_bt_connect_clicked(bool checked);
    void on_bt_play_clicked();
    void on_bt_pause_clicked(bool checked);
    void on_bt_stop_clicked();
    void on_bt_emergency_clicked();
    void on_bt_addSlicer_clicked();
    void updateTemp(double *temp_Extruders, double tempTable);
    void updateExt(double posX, double posY, double posZ);
    void on_cb_Extruder_qnt_currentTextChanged(const QString &arg1);
    void isPrintJobRunning(bool b);
    void on_bt_filamentoRetract_clicked();
    void on_bt_filamentoOneSpeed_clicked();
    void on_bt_filamentoTwoSpeed_clicked();
    void on_bt_saveConfig_clicked();
    void on_cb_printer_currentTextChanged(const QString &arg1);
    void on_actionEnglish_triggered();
    void on_bt_extruder1_clicked(bool checked);
    void on_bt_extruder2_clicked(bool checked);
    void on_bt_extruder3_clicked(bool checked);
    void on_bt_extruder4_clicked(bool checked);
    void on_tb_filamentFlow_textChanged(const QString &arg1);
    void on_tb_speedFeedFilament_textChanged(const QString &arg1);
    void on_tb_coolerfan_textChanged(const QString &arg1);
    void on_bt_Bed_clicked(bool checked);
    void on_tb_BedTempMC_textEdited(const QString &arg1);
    void on_tb_ExtruderTempMC_textEdited(const QString &arg1);
    void on_bt_up_Y_clicked();
    void on_bt_left_X_clicked();
    void on_bt_down_Y_clicked();
    void on_bt_right_X_clicked();
    void on_bt_up_Z_clicked();
    void on_bt_down_Z_clicked();

private:

    Ui::BrPrint3D *ui;
    double *tempMesa;
    double *tempExtruders;
    int extrudersInUse;
    bool isCommaDecimalMark;
    bool resetWhenConnect;
    QTranslator translator;
    Repetier *printer_object=NULL;
    QStringList *open_files;                            //Lista de arquivos abertos
    ThreadRoutine *temp=NULL;
    arduinoListener *ard_List;
    QString extruderTemperature="";         //Temperatura Default Extrusor
    QString bedTemperature="";            //Temperatura Default Mesa
    QString extruderMAXTemp="";             //Temperatura Maxima do Extrusor
    QString bedMAXTemp="";                //Temperatura Maxima da Mesa
    QString areaX="2";                       //Tamanho da mesa no eixo X
    QString areaY="2";                       //Tamanho da mesa no eixo Y
    QString areaZ="2";                       //Tamanho da mesa no eixo Z
    QString rateMoviment;                        //Taxa de Movimento da Mesa
    QString extruderSpeed;                       //Velocidade do Extrusor
    QString extruderRetraction;                  //Velocidade de Retracao do Extrusor
    QString extruderQnt;              //Quantidade de extrusores
    QString connectionType;
    QString transmissionRate;
    QString firmwareType;
    QString cacheSize;
    QString connectionPort;
    int resetOnConnect, resetOnEmergency, printLog, qntextruders;
    QString feedZ;
    QString extruderMAXVol;

    //Definicoes PLA
    QString extruder_temperature_PLA;           //Temperatura do Extrusor
    QString table_temperature_PLA;              //Temperatura da Mesa
    QString fil_espessure_PLA;                  //Espessura do Filamento

    //Definicoes ABS
    QString extruder_temperature_ABS;           //Temperatura do Extrusor
    QString table_temperature_ABS;              //Temperatura da Mesa
    QString fil_espessure_ABS;                  //Espessura do Filamento
    //Definicoes Slicer
    QString pathslicer;                         //Caminho do slicer
    QString pathcura;                           //Caminho Cura
    QString pathextern;                         //Caminho slicer externo

    //Lista de Pontos do gcode
    QList<Points*> gcodeDots;
    //
    QString pathGcode;                  //Caminho do GCODE

    bool garbage; //Garbage - variable unused

    void disableAxisButtons();
    void enableAxisButtons();
    void loadConfigs(QString q);
    void locate_Slicer();
    void locate_Cura();
    void connectSignals();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

};

#endif // BRPRINT3D_H
