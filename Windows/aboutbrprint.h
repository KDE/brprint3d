#ifndef ABOUTBRPRINT_H
#define ABOUTBRPRINT_H

#include <QWidget>

namespace Ui {
class aboutBrPrint;
}

class aboutBrPrint : public QWidget
{
    Q_OBJECT

public:
    explicit aboutBrPrint(QWidget *parent = 0);
    ~aboutBrPrint();

private:
    Ui::aboutBrPrint *ui;

};

#endif // ABOUTBRPRINT_H
