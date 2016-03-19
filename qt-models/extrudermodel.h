#ifndef EXTRUDERMODEL_H
#define EXTRUDERMODEL_H
//QtIncludes
#include <QtCore/QAbstractTableModel>
#include <QtCore/QTimer>
//LocalIncludes
#include "extruderobject.h"

class ExtruderModel : public QAbstractTableModel
{
public:
    ExtruderModel(int qntExtruders, QList<ExtruderObject> list);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    int m_qntExtruders;
    QList <ExtruderObject> extruderList;
    void updateExtruderTemp();
};

#endif // EXTRUDERMODEL_H
