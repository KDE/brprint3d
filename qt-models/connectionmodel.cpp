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
#include "connectionmodel.h"

ConnectionModel::ConnectionModel(ConnectObject *c)
{
    connect = c;
}

int ConnectionModel::rowCount(const QModelIndex &parent) const
{   Q_UNUSED(parent);
    return 5;
}

QVariant ConnectionModel::data(const QModelIndex &index, int role) const
{
        if(Qt::DisplayRole != role){
                return QVariant();
        }
        else{
            switch (index->row()){
            case 0: return connect->getSerialPort();
            case 1: return connect->getTransmissionRate();
            case 2: return connect->getCacheSize();
            case 3: return connect->getResetOnConnect();
            case 4: return connect->getPrintLog();
            }
        }
}

bool ConnectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole){
        switch (index.row()) {
            case 0: connect->setSerialPort(value.toString()); emit dataChanged(index,index);
            case 1: connect->setTransmissionRate(value.toInt()); emit dataChanged(index,index);
            case 2: connect->setCacheSize(value.toInt()); emit dataChanged(index,index);
            case 3: connect->setResetOnConnect(value.toBool()); emit dataChanged(index,index);
            case 4: connect->setPrintLog(value.toBool()); emit dataChanged(index,index);
        }
        return true;
    }
    return false;
}
