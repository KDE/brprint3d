#ifndef EXTRUDERCONTROLWIDGET_H
#define EXTRUDERCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class ExtruderControlWidget;
}

class ExtruderControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExtruderControlWidget(QWidget *parent = 0);
    ~ExtruderControlWidget();

private:
    Ui::ExtruderControlWidget *ui;
};

#endif // EXTRUDERCONTROLWIDGET_H
