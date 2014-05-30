#include "bedmodel.h"

bedModel::bedModel()
{
    timer.start(1000);
    connect(&timer, &QTimer::timeout, this, &bedModel::updateBedTemperature);
}

int bedModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant bedModel::data(const QModelIndex &index, int role) const
{
    if(Qt::DisplayRole != role)
            return QVariant();
        else{
            switch (index.row()){
            case 0: return bed.currTemp;
            case 1: return bed.desireTemp;
            case 2: return bed.areaX;
            case 3: return bed.areaY;
            case 4: return bed.areaZ;
            }
        }
}

bool bedModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
            switch(index.row()) {
                case 0:  bed.currTemp = value.toDouble(); emit dataChanged(index,index);break;
                case 1:  bed.desireTemp = value.toDouble(); emit dataChanged(index,index);break;
                case 2:  bed.areaX = value.toInt(); emit dataChanged(index,index);break;
                case 3:  bed.areaY = value.toInt(); emit dataChanged(index,index);break;
                case 4:  bed.areaZ = value.toInt(); emit dataChanged(index,index);break;
            }
        }
        return true;
}

Qt::ItemFlags bedModel::flags(const QModelIndex &index) const
{
    if(index.row == 0)
        return QAbstractListModel::flags(index);
    else
        return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void bedModel::updateBedTemperature()
{   /* Use rand to sort random temps to test, but when the project is more advanced substitute this
      for the info get from the printer
    */
    std::srand (time(NULL));
    const QVariant v(std::rand()%100);
    setData(index(0,0),v,Qt::EditRole);
}
