#ifndef BIGBUTTON_H
#define BIGBUTTON_H

#include <QWidget>

namespace Ui {
class BigButton;
}

class BigButton : public QWidget
{
    Q_OBJECT

public:
    explicit BigButton(QWidget *parent = 0);
    ~BigButton();

private:
    Ui::BigButton *ui;
};

#endif // BIGBUTTON_H
