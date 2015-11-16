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

#ifndef EXTRUDERCONTROLWIDGET_H
#define EXTRUDERCONTROLWIDGET_H

#include <qt5/QtWidgets/QWidget>
#include <stdio.h>

namespace Ui
{
class ExtruderControlWidget;
}

class ExtruderControlWidget : public QWidget
{
    Q_OBJECT
public:
explicit ExtruderControlWidget(QWidget *parent = 0);
~ExtruderControlWidget();
void init();

private:
    Ui::ExtruderControlWidget* ui;
private slots:
    void updatePos(double posX, double posY, double posZ);
};

#endif // EXTRUDERCONTROLWIDGET_H
