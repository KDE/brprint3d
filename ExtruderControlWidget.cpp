/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 Copyright (C) 2015 BRPrint3D Authors

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/
#include "ExtruderControlWidget.h"
#include "ui_ExtruderControlWidget.h"

ExtruderControlWidget::ExtruderControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtruderControlWidget)
{
    ui->setupUi(this);
    connect(ui->bt_homeX,&QPushButton::clicked,this,&ExtruderControlWidget::setHome);
    connect(ui->bt_homeY,&QPushButton::clicked,this,&ExtruderControlWidget::setHome);
    connect(ui->bt_homeZ,&QPushButton::clicked,this,&ExtruderControlWidget::setHome);
    connect(ui->bt_homeXYZ,&QPushButton::clicked,this,&ExtruderControlWidget::setHome);

    connect(ui->bt_leftX,&QPushButton::clicked,this,&ExtruderControlWidget::setPosX);
    connect(ui->bt_rightX,&QPushButton::clicked,this,&ExtruderControlWidget::setPosX);

    connect(ui->bt_upY,&QPushButton::clicked,this,&ExtruderControlWidget::setPosY);
    connect(ui->bt_downY,&QPushButton::clicked,this,&ExtruderControlWidget::setPosY);

    connect(ui->bt_upZ,&QPushButton::clicked,this,&ExtruderControlWidget::setPosZ);
    connect(ui->bt_downZ,&QPushButton::clicked,this,&ExtruderControlWidget::setPosZ);

    ui->bt_homeX->setIcon(QIcon(":/Icons/Icons/homeAxisX.png"));
    ui->bt_homeY->setIcon(QIcon(":/Icons/Icons/homeaxisY.png"));
    ui->bt_homeZ->setIcon(QIcon(":/Icons/Icons/homeAxisZ.png"));
    ui->bt_homeXYZ->setIcon(QIcon(":/Icons/Icons/homeAxisXYZ.png"));
    ui->bt_rightX->setIcon(QIcon(":/Icons/Icons/arrowRight.png"));
    ui->bt_leftX->setIcon(QIcon(":/Icons/Icons/arrowLeft.png"));
    ui->bt_upY->setIcon(QIcon(":/Icons/Icons/arrowUp.png"));
    ui->bt_downY->setIcon(QIcon(":/Icons/Icons/arrowDown.png"));
    ui->bt_upZ->setIcon(QIcon(":/Icons/Icons/arrowUp.png"));
    ui->bt_downZ->setIcon(QIcon(":/Icons/Icons/arrowDown.png"));
    ui->bt_filOneSpeed->setIcon(QIcon(":/Icons/Icons/extOut.png"));
    ui->bt_filTwoSpeed->setIcon(QIcon(":/Icons/Icons/extOut2.png"));
    ui->bt_filRetract->setIcon(QIcon(":/Icons/Icons/extruderRetract.png"));
    ui->lb_XY->setPixmap(QPixmap(":/Icons/Icons/axisXY.png"));
    ui->lb_axisZ->setPixmap(QPixmap(":/Icons/Icons/axisZ.png"));
    ui->lb_Extruder->setPixmap(QPixmap(":/Icons/Icons/filamentRetract.png"));

    connect(ui->bt_filRetract,&QPushButton::clicked,this,&ExtruderControlWidget::setFillExtruder);
    connect(ui->bt_filOneSpeed,&QPushButton::clicked,this,&ExtruderControlWidget::setFillExtruder);
    connect(ui->bt_filTwoSpeed,&QPushButton::clicked,this,&ExtruderControlWidget::setFillExtruder);
}

ExtruderControlWidget::~ExtruderControlWidget()
{
    delete ui;
}

void ExtruderControlWidget::init()
{
}

//This slot updates on UI the position of the Extruder
void ExtruderControlWidget::updatePos()
{
    ui->tb_axisXPos->setText(QString::number(printerObject->getCurrentXPos()));
    ui->tb_axisYPos->setText(QString::number(printerObject->getCurrentYPos()));
    ui->tb_axisZPos->setText(QString::number(printerObject->getCurrentZPos()));
}

// This function seems to have the wrong name: why it's get if it's not returning anything?
void ExtruderControlWidget::getPrinterObject(Repetier *pObject)
{
    printerObject = pObject;
    maxX = pObject->getMaxX();
    maxY = pObject->getMaxY();
    maxZ = pObject->getMaxZ();
}

void ExtruderControlWidget::setHome(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(!btn)
        return;

    if(btn == ui->bt_homeX) {
         printerObject->homeAxis('X');
    } else if (btn == ui->bt_homeY) {
        printerObject->homeAxis('Y');
    } else if (btn == ui->bt_homeZ) {
        printerObject->homeAxis('Z');
    } else if (btn == ui->bt_homeXYZ) {
        printerObject->homeAllAxis();
    }
}
void ExtruderControlWidget::setPosX()
{
    double pos = printerObject->getCurrentXPos();
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(btn == ui->bt_leftX)
        pos -= ui->cb_displacement->currentText().toDouble();
    else if(btn == ui->bt_rightX)
        pos += ui->cb_displacement->currentText().toDouble();
    if(pos >= 0 && pos<=maxX)
        printerObject->moveAxisToPos('X',pos);
}

void ExtruderControlWidget::setPosY()
{
    double pos = printerObject->getCurrentYPos();
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if(btn == ui->bt_upY)
        pos += ui->cb_displacement->currentText().toDouble();
    else if(btn == ui->bt_downY)
        pos -= ui->cb_displacement->currentText().toDouble();

    if(pos>=0 && pos<=maxY)
        printerObject->moveAxisToPos('Y',pos);
}

void ExtruderControlWidget::setPosZ()
{
    double pos = printerObject->getCurrentZPos();

    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(btn == ui->bt_upZ)
        pos += ui->cb_displacement->currentText().toDouble();
    else if(btn == ui->bt_downZ)
        pos -= ui->cb_displacement->currentText().toDouble();

    if(pos>=0 && pos<=maxZ)
        printerObject->moveAxisToPos('Z',pos);
}

void ExtruderControlWidget::disablePositionsButtons(bool b)
{
    ui->wg_ExtruderButtons->setDisabled(b);
}

void ExtruderControlWidget::setFillExtruder()
{
    QPushButton *btn  = qobject_cast<QPushButton*>(sender());

    if(btn == ui->bt_filRetract) {

    } else if(btn == ui->bt_filOneSpeed) {

    } else if(btn == ui->bt_filTwoSpeed) {

    }
}
