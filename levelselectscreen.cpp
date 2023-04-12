#include "levelselectscreen.h"
#include "ui_levelselectscreen.h"

LevelSelectScreen::LevelSelectScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelSelectScreen)
{
    ui->setupUi(this);
}

LevelSelectScreen::~LevelSelectScreen()
{
    delete ui;
}
