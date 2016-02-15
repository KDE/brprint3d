#ifndef EXTRUDERMODEL_H
#define EXTRUDERMODEL_H
#include <QAbstractTableModel>
#include "KI/Repetier.h"
#include <stdio.h>
#include <QTimer>

class extruderModel : public QAbstractTableModel
{
public:
    extruderModel();
    void setPrinterObjetc(Repetier *p);
private:
    int m_rowCount;
    int m_columnCount;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    Repetier *printerObject;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    QTimer timer;
    struct extruderObject;
    QList<extruderObject*> extruderList;
};

#endif // EXTRUDERMODEL_H
