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

#ifndef LEGALWARNING_H
#define LEGALWARNING_H

#include <QDialog>

namespace Ui
{
class LegalWarning;
}

class LegalWarning : public QDialog
{
    Q_OBJECT

public:
    explicit LegalWarning(QWidget *parent = 0);
    ~LegalWarning();

private:
    Ui::LegalWarning *ui;


};

#endif // LEGALWARNING_H
