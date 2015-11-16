/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include "ExtruderControlWidget.h"
#include "ui_ExtruderControlWidget.h"

ExtruderControlWidget::ExtruderControlWidget()
{
    ui = new Ui::ExtruderControlWidget;
    ui->setupUi(this);
}

ExtruderControlWidget::~ExtruderControlWidget()
{
    delete ui;
}
void ExtruderControlWidget::init()
{
    

}

//This slot update on UI the position of the Extruder
void ExtruderControlWidget::updatePos(double posX, double posY, double posZ)
{   //This function update the extruder position on the screen
    char resp[51];
    sprintf(resp, "%.3lf", posX);
    QString xx = QString::fromUtf8(resp);
    sprintf(resp, "%.3lf", posY);
    QString yy = QString::fromUtf8(resp);
    sprintf(resp, "%.3lf", posZ);
    QString zz = QString::fromUtf8(resp);
    ui->tb_axisXPos->setText(xx);
    ui->tb_axisYPos->setText(yy);
    ui->tb_axisZPos->setText(zz);

}

