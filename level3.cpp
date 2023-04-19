#include "level3.h"
#include "ui_level3.h"
#include "model.h"

Level3::Level3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level3)
{
    ui->setupUi(this);
    QPixmap pixmap(":/sprites/Resources/Map1.png");
    ui->label->setPixmap(pixmap.scaled(600, 600));

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &Level3::homeButtonClicked);

    // for temp button
    connect(ui->tempButton,
            &QPushButton::clicked,
            this,
            &Level3::successfullyParked);

    // for temp button
    connect(ui->tempButton_2,
            &QPushButton::clicked,
            this,
            &Level3::failed);
}

Level3::~Level3()
{
    delete ui;
}

void Level3::homeButtonClicked()
{
    Model::instance->goHome();
}


void Level3::on_checkButton_clicked()
{

}

void Level3::successfullyParked()
{
    Model::instance->successfulPark();
}

void Level3::failed()
{
    Model::instance->failedPark();
}
