#include "ExtruderControlWidget.h"
#include "ui_ExtruderControlWidget.h"

ExtruderControlWidget::ExtruderControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtruderControlWidget)
{
    ui->setupUi(this);
}

ExtruderControlWidget::~ExtruderControlWidget()
{
    delete ui;
}
