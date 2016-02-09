#include "extruderitem.h"
#include "ui_extruderitem.h"

extruderItem::extruderItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::extruderItem)
{
    ui->setupUi(this);
}

extruderItem::~extruderItem()
{
    delete ui;
}

void extruderItem::setExtruderNumber(int i)
{
    ui->extruderNumber->setText(QString::number(i));
}
