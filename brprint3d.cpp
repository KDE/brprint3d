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
}

BrPrint3D::~BrPrint3D()
{
    delete ui;
}
void BrPrint3D::init()
{
    vtkView = new vtkWidget();
    ui->_vtkConteiner->addWidget(vtkView);


}
