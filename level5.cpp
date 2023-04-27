/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

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

    connect(ui->instructionsButton,
            &QPushButton::clicked,
            this,
            &Level5::instructionsClicked);

    connect(Model::instance,
            &Model::level5Started,
            this,
            &Level5::prepareToShow);

    connect(ui->checkButton,
            &QPushButton::clicked,
            this,
            &Level5::checkPark);

    connect(Model::instance,
            &Model::showLevelFailure,
            this,
            &Level5::hideInstructionButton);

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
    ui->instructionsButton->hide();
    Model::instance->successfulPark();
}

void Level5::failed()
{
    ui->instructionsButton->hide();
    Model::instance->failedPark();
}

void Level5::instructionsClicked()
{
    Model::instance->showInstructions(this);
}

void Level5::prepareToShow()
{
    ui->instructionsButton->show();
}

void Level5::hideInstructionButton()
{
    ui->instructionsButton->hide();
}

void Level5::checkPark()
{
    if (Model::instance->carModel->isParkedSuccessfully)
        successfullyParked();
    else
        failed();
}

