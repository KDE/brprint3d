#include "BigButton.h"
#include "ui_BigButton.h"

BigButton::BigButton(QWidget *parent, QString name, bool isCheckable) :
    QWidget(parent),
    ui(new Ui::BigButton)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->pushButton->setCheckable(isCheckable);
}

BigButton::~BigButton()
{
    delete ui;
}
