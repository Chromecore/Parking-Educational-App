#include "level2.h"
#include "ui_level2.h"
#include "model.h"

Level2::Level2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level2)
{
    ui->setupUi(this);
    QPixmap pixmap(":/sprites/Resources/Map1.png");
    ui->label->setPixmap(pixmap.scaled(600, 600));
    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &Level2::on_homeButton_clicked);

    // for temp button
    connect(ui->tempButton,
            &QPushButton::clicked,
            this,
            &Level2::successfullyParked);

    // for temp button
    connect(ui->tempButton_3,
            &QPushButton::clicked,
            this,
            &Level2::failed);
}

Level2::~Level2()
{
    delete ui;
}

void Level2::on_homeButton_clicked()
{
    Model::instance->goHome();
}


void Level2::on_checkButton_clicked()
{

}


void Level2::on_tempButton_clicked()
{

}


void Level2::on_tempButton_3_clicked()
{

}
void Level2::successfullyParked()
{
    Model::instance->successfulPark();
}

void Level2::failed()
{
    Model::instance->failedPark();
}
