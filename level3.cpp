#include "level3.h"
#include "ui_level3.h"

Level3::Level3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level3)
{
    ui->setupUi(this);
}

Level3::~Level3()
{
    delete ui;
}
