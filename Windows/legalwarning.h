#ifndef LEGALWARNING_H
#define LEGALWARNING_H

#include <QWidget>

namespace Ui {
class LegalWarning;
}

class LegalWarning : public QWidget
{
    Q_OBJECT

public:
    explicit LegalWarning(QWidget *parent = 0);
    ~LegalWarning();

private:
    Ui::LegalWarning *ui;


};

#endif // LEGALWARNING_H
