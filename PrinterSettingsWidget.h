#ifndef PRINTERSETTINGSWIDGET_H
#define PRINTERSETTINGSWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "PrinterSettings.h"
#include "arduinolistener.h"

namespace Ui {
class PrinterSettingsWidget;
}

class PrinterSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterSettingsWidget(QWidget *parent = 0);
    ~PrinterSettingsWidget();
    void init();
    PrinterSettings getCurrentSettings();
    void setConnectionPorts(QStringList list);

private slots:
    void disableExtrudersQntCb(bool d);
    void locateArduino();

    void on_cb_ExtruderQnt_currentTextChanged(const QString &arg1);

private:
    Ui::PrinterSettingsWidget *ui;
    int extrudersInUse;
    arduinoListener *arduino_Listener;
    bool garbage;
signals:
   void s_extrudersInUse(int n);
};

#endif // PRINTERSETTINGSWIDGET_H