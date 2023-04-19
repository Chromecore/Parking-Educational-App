#include "level5.h"
#include "ui_level5.h"
#include "model.h"

Level5::Level5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level5)
{
    ui->setupUi(this);

    QPixmap pixmap(":/sprites/Resources/Map1.png");
    ui->label->setPixmap(pixmap.scaled(600, 600));

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &Level5::homeButtonClicked);

    // for temp button
    connect(ui->tempButton,
            &QPushButton::clicked,
            this,
            &Level5::successfullyParked);

    // for temp button
    connect(ui->tempButton_2,
            &QPushButton::clicked,
            this,
            &Level5::failed);
}

Level5::~Level5()
{
    delete ui;
}

void Level5::homeButtonClicked()
{
    Model::instance->goHome();
}

void Level5::successfullyParked()
{
    Model::instance->successfulPark();
}

void Level5::failed()
{
    Model::instance->failedPark();
}

