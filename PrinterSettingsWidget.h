#ifndef PRINTERSETTINGSWIDGET_H
#define PRINTERSETTINGSWIDGET_H

#include <QWidget>
#include "PrinterSettings.h"

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
    void on_cb_Extruder_qnt_currentTextChanged(const QString &arg1);
    void disableExtrudersQntCb(bool d);

private:
    Ui::PrinterSettingsWidget *ui;
    int extrudersInUse;
signals:
   void s_hideExtruders(int n);
   void s_extrudersInUse(int n);
};

#endif // PRINTERSETTINGSWIDGET_H
