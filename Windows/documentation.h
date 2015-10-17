#ifndef DOCUMENTATION_H
#define DOCUMENTATION_H

#include <QWidget>

namespace Ui {
class Documentation;
}

class Documentation : public QWidget
{
    Q_OBJECT

public:
    explicit Documentation(QWidget *parent = 0);
    ~Documentation();

private:
    Ui::Documentation *ui;

};

#endif // DOCUMENTATION_H
