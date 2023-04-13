/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include "welcomescreen.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showWelcomeWidget();

    connect(Model::instance,
            &Model::tutorialStarted,
            this,
            &MainWindow::showLevel1Widget);

    connect(Model::instance,
            &Model::runningLevelSelect,
            this,
            &MainWindow::showLevelSelectWidget);

    connect(Model::instance,
            &Model::runningCarWidget,
            this,
            &MainWindow::showCarWidget);

    connect(Model::instance,
            &Model::goingHome,
            this,
            &MainWindow::showWelcomeWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit Model::instance->keyPressed(event);
}

void MainWindow::showWelcomeWidget()
{
    hideAllWidgets();
    ui->welcomeWidget->show();
}

void MainWindow::showCarWidget()
{
    hideAllWidgets();
    ui->carWidget->show();
}

void MainWindow::showLevel1Widget()
{
    hideAllWidgets();
    ui->level1Widget->show();
    ui->carWidget->show();
}

void MainWindow::showLevelSelectWidget()
{
    hideAllWidgets();
    ui->levelSelectWidget->show();
}

void MainWindow::hideAllWidgets()
{
    ui->carWidget->hide();
    ui->welcomeWidget->hide();
    ui->level1Widget->hide();
    ui->levelSelectWidget->hide();
    ui->widget_2->hide();
    ui->widget_3->hide();
}
