#include "levelselectscreen.h"
#include "ui_levelselectscreen.h"
#include "model.h"

LevelSelectScreen::LevelSelectScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelSelectScreen)
{
    ui->setupUi(this);

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &LevelSelectScreen::homeButtonClicked);

    connect(ui->level1Button,
            &QPushButton::clicked,
            this,
            &LevelSelectScreen::level1ButtonClicked);

    connect(ui->level2Button,
            &QPushButton::clicked,
            this,
            &LevelSelectScreen::level2ButtonClicked);

    connect(ui->level3Button,
            &QPushButton::clicked,
            this,
            &LevelSelectScreen::level3ButtonClicked);

    connect(ui->level4Button,
            &QPushButton::clicked,
            this,
            &LevelSelectScreen::level4ButtonClicked);

    connect(ui->level5Button,
            &QPushButton::clicked,
            this,
            &LevelSelectScreen::level5ButtonClicked);
}

LevelSelectScreen::~LevelSelectScreen()
{
    delete ui;
}

void LevelSelectScreen::homeButtonClicked()
{
    Model::instance->goHome();
}

void LevelSelectScreen::level1ButtonClicked()
{
    Model::instance->runLevel1();
}

void LevelSelectScreen::level2ButtonClicked()
{
    Model::instance->runLevel2();
}

void LevelSelectScreen::level3ButtonClicked()
{
    Model::instance->runLevel3();
}

void LevelSelectScreen::level4ButtonClicked()
{
    Model::instance->runLevel4();
}

void LevelSelectScreen::level5ButtonClicked()
{
    Model::instance->runLevel5();
}
