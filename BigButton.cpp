#include "BigButton.h"
#include "ui_BigButton.h"

BigButton::BigButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigButton)
{
    ui->setupUi(this);
}

BigButton::~BigButton()
{
    delete ui;
}
