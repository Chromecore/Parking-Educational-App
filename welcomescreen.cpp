/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include "model.h"
#include <QMovie>

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);

    movie = new QMovie(":/sprites/Resources/badParking.gif");
    movie->setScaledSize(ui->movieLabel->size());
    ui->movieLabel->setMovie(movie);
    movie->start();

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
    delete movie;
}

void WelcomeScreen::onStartButtonClicked()
{
    Model::instance->runLevel1();
}

void WelcomeScreen::onLevelSelectClicked()
{
    Model::instance->runLevelSelect();
}
