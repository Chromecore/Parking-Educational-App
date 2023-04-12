#include "level1.h"
#include "ui_level1.h"

Level1::Level1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level1)
{
    ui->setupUi(this);
    setStyleSheet("background-image: :/sprites/Resources/Map1.png");
}

Level1::~Level1()
{
    delete ui;
}
