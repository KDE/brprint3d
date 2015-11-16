#ifndef PRINTERSETTINGSWIDGET_H
#define PRINTERSETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class PrinterSettingsWidget;
}

class PrinterSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterSettingsWidget(QWidget *parent = 0);
    ~PrinterSettingsWidget();

private:
    Ui::PrinterSettingsWidget *ui;
};

#endif // PRINTERSETTINGSWIDGET_H
