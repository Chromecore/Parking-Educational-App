#include "fail.h"
#include "ui_fail.h"

Fail::Fail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fail)
{
    ui->setupUi(this);
}

Fail::~Fail()
{
    delete ui;
}
