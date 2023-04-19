#include "level4.h"
#include "ui_level4.h"

Level4::Level4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level4)
{
    ui->setupUi(this);
}

Level4::~Level4()
{
    delete ui;
}
