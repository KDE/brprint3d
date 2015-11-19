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
    explicit BigButton(QWidget *parent = 0, QString name = "", bool isCheckable = false, QString pix = "");
    ~BigButton();
public slots:
    bool getCheckedStatus();
    void setIcon(QString pix);
    void setChecked(bool b);

private:
    Ui::BigButton *ui;
signals:
    void clicked(bool checked);
};

#endif // BIGBUTTON_H
