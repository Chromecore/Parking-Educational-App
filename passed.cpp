#include "passed.h"
#include "ui_passed.h"

Passed::Passed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Passed)
{
    ui->setupUi(this);
}

Passed::~Passed()
{
    delete ui;
}
