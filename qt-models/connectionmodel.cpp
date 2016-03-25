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
