#include "extrudermodel.h"

ExtruderModel::ExtruderModel(int qntExtruders, QList<ExtruderObject> list)
{
    m_qntExtruders = qntExtruders;
    extruderList = list;
}

int ExtruderModel::rowCount(const QModelIndex &parent) const
{   Q_UNUSED(parent);
    return 6;
}

int ExtruderModel::columnCount(const QModelIndex &parent) const
{   Q_UNUSED(parent);
    return m_qntExtruders;
}

QVariant ExtruderModel::data(const QModelIndex &index, int role) const
{
    if(Qt::DisplayRole != role)
        return QVariant();
    else{
        //Maybe use pointer here???
        ExtruderObject tmp = extruderList.at(index.row());
        switch (index.column()){
            case 0: return tmp.currTemp;
            case 1: return tmp.getMaxTemp();
            case 2: return tmp.getExtrusionSpeed();
            case 3: return tmp.getFanSpeed();
            case 4: return tmp.getMovSpeed();
        }
    }
}

bool ExtruderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{   //Maybe use pointer??
    ExtruderObject tmp = extruderList.at(index.row());
    if (role == Qt::EditRole) {
        switch(index.column()) {
            case 1:  tmp.setMaxTemp(value.toInt()); emit dataChanged(index,index);
            case 2:  tmp.setExtrusionSpeed(value.toInt()); emit dataChanged(index,index);
            case 3:  tmp.setFanSpeed(value.toInt()); emit dataChanged(index,index);
            case 4:  tmp.setMovSpeed(value.toInt()); emit dataChanged(index,index);
         }
    }else if(role == Qt::DisplayRole){
        if(index.column() == 0){
            tmp.currTemp = value.toDouble();
            emit dataChanged(index,index);
        }
    }
    return true;//Right place?
}

Qt::ItemFlags ExtruderModel::flags(const QModelIndex &index) const
{   if(index.column()!=0)
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    else
        return QAbstractTableModel::flags(index);
}

void ExtruderModel::updateExtruderTemp()
{   /* Use rand to sort random temps to test, but when the project is more advanced substitute this
      for the info get from the printer */
    std::srand (time(NULL));
    for(int i=0; i < rowCount(QModelIndex()) ; i++){
        const QVariant v(std::rand()%100);
        setData(index(i,0),v ,Qt::DisplayRole); //Check this flag
    }

}
