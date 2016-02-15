#include "extrudermodel.h"

struct extruderObject{
 int index;
 double temperature;
 int retract;
};

extruderModel::extruderModel()
{
}

void extruderModel::setPrinterObjetc(Repetier *p)
{
    printerObject = p;
    for(int i=0;i<printerObject->getNoOfExtruders();i++){
    }
}

int extruderModel::rowCount(const QModelIndex &parent) const
{   Q_UNUSED(parent);
    return 4;
}

int extruderModel::columnCount(const QModelIndex &parent) const
{
    return 3;//printerObject->getNoOfExtruders();
}

QVariant extruderModel::data(const QModelIndex &index, int role) const
{
   // double *temperatures = printerObject->getAllExtrudersTemp();
    if(Qt::DisplayRole != role)
        return QVariant();
    else{

        switch (index.column()) {
        case 0:{
            return 10;//temperatures[index.row()];
        }break;
        case 1:{
            //Cooler Fan
            return 20;
        }break;
        case 2:{
            //Extruder/Retract
            return 30;
        }break;

        default:
            break;
        }
    }
}

bool extruderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
}

QVariant extruderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
       {
           if (orientation == Qt::Horizontal) {
               switch (section)
               {
               case 0:
                   return QString("Temperature");
               case 1:
                   return QString("Cooler Fan");
               case 2:
                   return QString("Extruder/Retract");
               }
           }
           if(orientation == Qt::Vertical){
               switch (section) {
               case 0:
                  return QString("Extruder One");
                   break;
               default:
                   break;
               }
           }
       }
    return QVariant();
}

Qt::ItemFlags extruderModel::flags(const QModelIndex &index) const
{
}
