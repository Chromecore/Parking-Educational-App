/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

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
            &Level2::homeButtonClicked);

    connect(ui->instructionsButton,
            &QPushButton::clicked,
            this,
            &Level2::instructionsClicked);

    connect(Model::instance,
            &Model::level2Started,
            this,
            &Level2::prepareToShow);

    connect(ui->checkButton,
            &QPushButton::clicked,
            this,
            &Level2::checkPark);

    connect(Model::instance,
            &Model::showLevelFailure,
            this,
            &Level2::hideInstructionButton);

    // for temp button
    connect(ui->tempButton,
            &QPushButton::clicked,
            this,
            &Level2::successfullyParked);

    // for temp button
    connect(ui->tempButton_2,
            &QPushButton::clicked,
            this,
            &Level2::failed);
}

Level2::~Level2()
{
    delete ui;
}

void Level2::homeButtonClicked()
{
    Model::instance->goHome();
}

void Level2::successfullyParked()
{
    ui->instructionsButton->hide();
    Model::instance->successfulPark();
}

void Level2::failed()
{
    ui->instructionsButton->hide();
    Model::instance->failedPark();
}

void Level2::instructionsClicked()
{
    Model::instance->showInstructions(this);
}

void Level2::prepareToShow()
{
    ui->instructionsButton->show();
}

void Level2::hideInstructionButton()
{
    ui->instructionsButton->hide();
}

void Level2::checkPark()
{
    if (Model::instance->carModel->isParkedSuccessfully)
        successfullyParked();
    else
        failed();
}
