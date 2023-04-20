#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include "model.h"

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);

    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &WelcomeScreen::onStartButtonClicked);

    connect(ui->levelSelectButton,
            &QPushButton::clicked,
            this,
            &WelcomeScreen::onLevelSelectClicked);
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::onStartButtonClicked()
{
    Model::instance->runLevel1();
}

void WelcomeScreen::onLevelSelectClicked()
{
    Model::instance->runLevelSelect();
}
