#ifndef BEDMODEL_H
#define BEDMODEL_H

#include <QAbstractListModel>
#include <QTimer>

class bedObject{
    double currTemp;
    double desireTemp;
    int areaX;
    int areaY;
    int areaZ;
};

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
    bedObject bed;
    void updateBedTemperature();
    QTimer timer;
};

#endif // BEDMODEL_H
