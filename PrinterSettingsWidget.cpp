#include "PrinterSettingsWidget.h"
#include "ui_PrinterSettingsWidget.h"

PrinterSettingsWidget::PrinterSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrinterSettingsWidget)
{
    ui->setupUi(this);
}

PrinterSettingsWidget::~PrinterSettingsWidget()
{
    delete ui;
}
