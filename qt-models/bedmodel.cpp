#include "bedmodel.h"

BedModel::BedModel(bedObject *b)
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
