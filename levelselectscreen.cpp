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
