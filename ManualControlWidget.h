#ifndef MANUALCONTROLWIDGET_H
#define MANUALCONTROLWIDGET_H
#include "ExtruderControlWidget.h"
#include <QWidget>
#include <KI/Repetier.h>
#include <threadRotine.h>
#include <QTabWidget>
#include <QSettings>
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <stdio.h>
namespace Ui {
class ManualControlWidget;
}

class ManualControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManualControlWidget(QWidget *parent = 0);
    ~ManualControlWidget();
    void init();
    void setGcodePreview(QString t);
    void startThreadRoutine();
    void stopThreadRoutine();
    void setBedStatus(bool b);
    void setExtruderStatus(bool b);
    void getPrinterObject(Repetier *printer_object);
    void setInitialMarks();
    ThreadRoutine *temp=NULL;

private:
    Ui::ManualControlWidget *ui;
    Repetier *printer_object;
    int qntExtruders,extrudersInUse;
    QString pathslicer,pathcura;
    void locateSlicer();
    void locateCura();
    QSettings settings;
    bool garbage,playStatus;
   
};

#endif // MANUALCONTROLWIDGET_H
