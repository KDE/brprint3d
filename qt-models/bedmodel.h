#ifndef BEDMODEL_H
#define BEDMODEL_H

#include <QAbstractListModel>

class bedModel : public QAbstractListModel
{
    Q_OBJECT
public:
    bedModel();

private:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // BEDMODEL_H
