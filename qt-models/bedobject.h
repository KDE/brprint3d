/*=====================================================================

 BrPrint3D, Open Source 3D Printing Host

 Copyright (C) 2015 BRPrint3D Authors

 This file is part of the BrPrint3D project

 BrPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BrPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BrPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/
#ifndef BEDOBJECT_H
#define BEDOBJECT_H

#include <QObject>

class BedObject : QObject
{
    Q_OBJECT

    Q_PROPERTY(int areaX READ areaX WRITE setAreaX NOTIFY areaXChanged)
    Q_PROPERTY(int areaY READ areaY WRITE setAreaY NOTIFY areaYChanged)
    Q_PROPERTY(int areaZ READ areaZ WRITE setAreaZ NOTIFY areaZChanged)
    Q_PROPERTY(double desireTemp READ desireTemp WRITE setDesireTemp NOTIFY desireTempChanged)
    Q_PROPERTY(double currTemp READ currTemp WRITE setCurrTemp NOTIFY currTempChanged)

public:
    BedObject(int x, int y, int z);
    double m_currTemp;
    double getDesireTemp();
    void setDesireTemp(double t);

    int areaX() const;
    int areaY() const;
    int areaZ() const;
    double desireTemp() const; //Desire Temp
    double currTemp() const;//Current Temp

    void setAreaX(const int &x);
    void setAreaY(const int &y);
    void setAreaZ(const int &z);
    void setdDesireTemp(const double &t);
    void setCurrTemp(const double &t);

private:
    double m_desireTemp;
    int m_areaX;
    int m_areaY;
    int m_areaZ;

signals:
    void areaXChanged(const int &x);
    void areaYChanged(const int &y);
    void areaZChanged(const int &z);
    void desireTempChanged(const double &t);
    void currTempChanged(const double &t);


};

#endif // BEDOBJECT_H
