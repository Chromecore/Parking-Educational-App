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

    connect(ui->instructionsButton,
            &QPushButton::clicked,
            this,
            &Level3::instructionsClicked);

    connect(Model::instance,
            &Model::level3Started,
            this,
            &Level3::prepareToShow);

    connect(ui->checkButton,
            &QPushButton::clicked,
            this,
            &Level3::checkPark);

    connect(Model::instance,
            &Model::showLevelFailure,
            this,
            &Level3::hideInstructionButton);

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

void Level3::successfullyParked()
{
    ui->instructionsButton->hide();
    Model::instance->successfulPark();
}

void Level3::failed()
{
    ui->instructionsButton->hide();
    Model::instance->failedPark();
}

void Level3::instructionsClicked()
{
    Model::instance->showInstructions(this);
}

void Level3::prepareToShow()
{
    ui->instructionsButton->show();
}

void Level3::hideInstructionButton()
{
    ui->instructionsButton->hide();
}

void Level3::checkPark()
{
    if (Model::instance->carModel->isParkedSuccessfully)
        successfullyParked();
    else
        failed();
}
