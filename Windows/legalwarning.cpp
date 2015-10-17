#include "legalwarning.h"
#include "ui_legalwarning.h"

LegalWarning::LegalWarning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LegalWarning)
{
    ui->setupUi(this);
}

LegalWarning::~LegalWarning()
{
    delete ui;
}
