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
}

LevelSelectScreen::~LevelSelectScreen()
{
    delete ui;
}

void LevelSelectScreen::homeButtonClicked()
{
    Model::instance->goHome();
}
