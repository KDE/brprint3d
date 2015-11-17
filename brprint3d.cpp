/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 (c) 2015 BRPrint3D Authors

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

#include "brprint3d.h"
#include "ui_Pandora.h"

BrPrint3D::BrPrint3D(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::BrPrint3D)
{
    ui->setupUi(this);
    BigButton *bt_import = new BigButton(0,"Import GCode");
    BigButton *bt_open = new BigButton(0,"Open File");
    BigButton *bt_connect = new BigButton(0,"Connect");
    BigButton *bt_play = new BigButton(0,"Play");
    BigButton *bt_pause = new BigButton(0,"Pause");
    BigButton *bt_stop = new BigButton(0,"Stop");
    BigButton *bt_stopOnEmergency = new BigButton(0,"Emergency Stop");
}

BrPrint3D::~BrPrint3D()
{
    delete ui;
}
void BrPrint3D::init()
{
    vtkView = new vtkWidget();
    ui->_vtkConteiner->addWidget(vtkView);
    connect(ui->_PrinterSettings,SIGNAL(s_extrudersInUse(int)),ui->_ManualControl,SLOT(setExtrudersInUse(int)));

}
