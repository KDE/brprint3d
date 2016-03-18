#ifndef BEDMODEL_H
#define BEDMODEL_H

//QtIncludes
#include <QAbstractListModel>
#include <QTimer>

//Local Includes
#include "bedobject.h"

class BedModel : public QAbstractListModel
{
    Q_OBJECT
public:
    BedModel(bedObject *b);

private:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    bedObject *bed;
    void updateBedTemperature();
    QTimer timer;
};

#endif // BEDMODEL_H
