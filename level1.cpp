#include "level1.h"
#include "ui_level1.h"
#include "model.h"

Level1::Level1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level1)
{
    ui->setupUi(this);

    QPixmap pixmap(":/sprites/Resources/Map1.png");
    ui->label->setPixmap(pixmap.scaled(600, 600));

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &Level1::homeButtonClicked);

    // for temp button
    connect(ui->tempButton,
            &QPushButton::clicked,
            this,
            &Level1::successfullyParked);

    // for temp button
    connect(ui->tempButton_2,
            &QPushButton::clicked,
            this,
            &Level1::failed);
}

Level1::~Level1()
{
    delete ui;
}

void Level1::homeButtonClicked()
{
    Model::instance->goHome();
}

void Level1::successfullyParked()
{
    Model::instance->successfulPark();
}

void Level1::failed()
{
    Model::instance->failedPark();
}

