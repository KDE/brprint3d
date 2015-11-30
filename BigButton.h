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
#ifndef BIGBUTTON_H
#define BIGBUTTON_H

#include <QWidget>
#include <QtGui/QIcon>

namespace Ui {
class BigButton;
}

class BigButton : public QWidget
{
    Q_OBJECT

public:
    explicit BigButton(QWidget *parent, const QString& name, const QString& pix, bool isCheckable = false);
    ~BigButton();

    bool isChecked();
    void setIcon(const QIcon& icon);
    void setChecked(bool b);

private:
    Ui::BigButton *ui;
signals:
    void clicked(bool checked);
};

#endif // BIGBUTTON_H
