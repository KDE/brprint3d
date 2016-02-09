#include "extruderitem.h"
#include "ui_extruderitem.h"

extruderItem::extruderItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::extruderItem)
{
    ui->setupUi(this);
    connect(ui->sp_temperature,&QSpinBox::editingFinished,this,&extruderItem::editingFinished);
    connect(ui->bt_startHeat,&QPushButton::clicked,this,&extruderItem::startHeat);
}

extruderItem::~extruderItem()
{
    delete ui;
}

void extruderItem::setExtruderNumber(int i)
{
    ui->extruderNumber->setText(QString::number(i));
}

int extruderItem::getExtruderTemp()
{
    return ui->sp_temperature->value();
}

QSpinBox* extruderItem::getSpinPointer()
{
    return ui->sp_temperature;
}

QPushButton* extruderItem::getButtonPointer(){
    return ui->bt_startHeat;
}

void extruderItem::setCurrTemperature(int v)
{
    ui->lb_currTemp->setText(QString::number(v)+" ºC");
}
