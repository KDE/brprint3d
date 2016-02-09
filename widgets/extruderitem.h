#ifndef EXTRUDERITEM_H
#define EXTRUDERITEM_H

#include <QWidget>

namespace Ui {
class extruderItem;
}

class extruderItem : public QWidget
{
    Q_OBJECT

public:
    explicit extruderItem(QWidget *parent = 0);
    ~extruderItem();
    void setExtruderNumber(int i);

private:
    Ui::extruderItem *ui;
};

#endif // EXTRUDERITEM_H
