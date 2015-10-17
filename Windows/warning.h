#ifndef WARNING_H
#define WARNING_H

#include <QDialog>

namespace Ui {
class warning;
}

class warning : public QDialog
{
    Q_OBJECT

public:
    explicit warning(QWidget *parent = 0);
    ~warning();

private:
    Ui::warning *ui;

};

#endif // WARNING_H
