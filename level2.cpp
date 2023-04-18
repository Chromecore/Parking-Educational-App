#include "level2.h"
#include "ui_level2.h"

Level2::Level2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level2)
{
    ui->setupUi(this);
}

Level2::~Level2()
{
    delete ui;
}
