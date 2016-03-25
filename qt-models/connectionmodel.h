#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H
//QtIncludes
#include <QtCore/QAbstractListModel>

//Local Includes
#include "connectobject.h"

class connectionModel : public QAbstractListClass
{
public:
    connectionModel(ConnectObject *c);

private:
    //Override Methods
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    ConnectObject *connect;
};

#endif // CONNECTIONMODEL_H
