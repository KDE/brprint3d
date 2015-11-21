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
#ifndef EXTRUDERCONTROLWIDGET_H
#define EXTRUDERCONTROLWIDGET_H

#include <QWidget>
#include "Repetier.h"

namespace Ui {
class ExtruderControlWidget;
}

class ExtruderControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExtruderControlWidget(QWidget *parent = 0);
    ~ExtruderControlWidget();

    void init();
    void getPrinterObject(Repetier *pObject);
public slots:
    void disablePositionsButtons(bool b);

    private:
        Ui::ExtruderControlWidget* ui;
        Repetier *printerObject=nullptr;
        double maxX=0,maxY=0,maxZ=0;
    private slots:
        void updatePos(double posX, double posY, double posZ);
        void setHomeX();
        void setHomeY();
        void setHomeZ();
        void setHomeXYZ();
        void setPosX();
        void setPosY();
        void setPosZ();


};

#endif // EXTRUDERCONTROLWIDGET_H
