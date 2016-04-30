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
#include "bedmodel.h"

BedModel::BedModel(BedObject *b)
{   bed = b;
    timer.start(1000);
    connect(&timer, &QTimer::timeout, this, &BedModel::updateBedTemperature);
}

int BedModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant BedModel::data(const QModelIndex &index, int role) const
{
    if(Qt::DisplayRole != role)
            return QVariant();
        else{
            switch (index.row()){
            case 0: return bed->currTemp;
            case 1: return bed->getDesireTemp();
            case 2: return bed->getX();
            case 3: return bed->getY();
            case 4: return bed->getZ();
            }
        }
}
/*
    Remove the set's of the area of the printer, because this model only will be constructed
    when the printer is connect, and because of that, the value of the print area cant be
    changed.
*/
bool BedModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
            switch(index.row()) {
                case 0:  bed->currTemp = value.toDouble(); emit dataChanged(index,index);break;
                case 1:  bed->setDesireTemp(value.toDouble()); emit dataChanged(index,index);break;
            }
            return true;
        }
     return false;
}

Qt::ItemFlags BedModel::flags(const QModelIndex &index) const
{
    if(index.row() == 0)
        return QAbstractListModel::flags(index);
    else
        return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void BedModel::updateBedTemperature()
{   /* Use rand to sort random temps to test, but when the project is more advanced substitute this
      for the info get from the printer
    */
    std::srand (time(NULL));
    const QVariant v(std::rand()%100);
    setData(index(0,0),v,Qt::EditRole);
}
