/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

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

    connect(ui->instructionsButton,
            &QPushButton::clicked,
            this,
            &Level1::instructionsClicked);

    connect(Model::instance,
            &Model::level1Started,
            this,
            &Level1::prepareToShow);

    connect(ui->checkButton,
            &QPushButton::clicked,
            this,
            &Level1::checkPark);

    connect(Model::instance,
            &Model::showLevelFailure,
            this,
            &Level1::hideInstructionButton);

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
    ui->instructionsButton->hide();
    Model::instance->successfulPark();
}

void Level1::failed()
{
    ui->instructionsButton->hide();
    Model::instance->failedPark();
}

void Level1::instructionsClicked()
{
    Model::instance->showInstructions(this);
}

void Level1::prepareToShow()
{
    ui->instructionsButton->show();
}

void Level1::hideInstructionButton()
{
    ui->instructionsButton->hide();
}

void Level1::checkPark()
{
    if (Model::instance->carModel->isParkedSuccessfully)
        successfullyParked();
    else
        failed();
}

