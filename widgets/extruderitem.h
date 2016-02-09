#ifndef EXTRUDERITEM_H
#define EXTRUDERITEM_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

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
    int getExtruderTemp();
    QSpinBox *getSpinPointer();
    QPushButton *getButtonPointer();

private:
    Ui::extruderItem *ui;
signals:
    void editingFinished();
    void startHeat();
};

#endif // EXTRUDERITEM_H
