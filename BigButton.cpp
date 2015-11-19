#include "BigButton.h"
#include "ui_BigButton.h"

BigButton::BigButton(QWidget *parent, QString name, bool isCheckable, QString iconPath) :
    QWidget(parent),
    ui(new Ui::BigButton)
{   QPixmap pix(iconPath);
    ui->setupUi(this);
    ui->label->setText(name);
    ui->pushButton->setCheckable(isCheckable);
    connect(ui->pushButton,&QPushButton::clicked,this,&BigButton::clicked);
    ui->pushButton->setIcon(QIcon(pix));
    ui->pushButton->setIconSize(QSize(50,50));
}

BigButton::~BigButton()
{
    delete ui;
}
bool BigButton::getCheckedStatus(){

    return ui->pushButton->isChecked();

}
void BigButton::setIcon(QString pix){
    ui->pushButton->setIcon(QIcon(pix));
}
