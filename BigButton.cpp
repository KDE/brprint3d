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
#include "BigButton.h"
#include "ui_BigButton.h"

BigButton::BigButton(QWidget *parent, const QString& name,const QString& iconPath,  bool isCheckable) :
    QWidget(parent),
    ui(new Ui::BigButton)
{   
    ui->setupUi(this);
    ui->label->setText(name);
    ui->pushButton->setCheckable(isCheckable);
    ui->pushButton->setIcon(QIcon(iconPath));
    //The value bellow is the best size that the icon could have on the button
    ui->pushButton->setIconSize(QSize(50,50));
    connect(ui->pushButton, &QPushButton::clicked, this, &BigButton::clicked);
}

BigButton::~BigButton()
{
    delete ui;
}

bool BigButton::isChecked()
{
    return ui->pushButton->isChecked();
}

void BigButton::setIcon(const QIcon& icon)
{
    ui->pushButton->setIcon(icon);
}

void BigButton::setChecked(bool b)
{
    ui->pushButton->setChecked(b);
}
