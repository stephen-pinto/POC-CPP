#include "generatehashform.h"
#include "ui_generatehashform.h"

GenerateHashForm::GenerateHashForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenerateHashForm)
{
    ui->setupUi(this);
}

GenerateHashForm::~GenerateHashForm()
{
    delete ui;
}
