#include "level4.h"
#include "ui_level4.h"
#include "model.h"

Level4::Level4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level4)
{
    ui->setupUi(this);

    QPixmap pixmap(":/sprites/Resources/Map1.png");
    ui->label->setPixmap(pixmap.scaled(600, 600));

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &Level4::homeButtonClicked);

    // for temp button
    connect(ui->tempButton,
            &QPushButton::clicked,
            this,
            &Level4::successfullyParked);

    // for temp button
    connect(ui->tempButton_2,
            &QPushButton::clicked,
            this,
            &Level4::failed);
}

Level4::~Level4()
{
    delete ui;
}

void Level4::homeButtonClicked()
{
    Model::instance->goHome();
}

void Level4::successfullyParked()
{
    Model::instance->successfulPark();
}

void Level4::failed()
{
    Model::instance->failedPark();
}

