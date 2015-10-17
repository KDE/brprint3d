#ifndef LOADING_H
#define LOADING_H
#include <QDialog>

namespace Ui {
class Loading;
}

class Loading : public QDialog
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = 0);
    ~Loading();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Loading *ui;

};

#endif // LOADING_H
