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

    connect(Model::instance,
            &Model::level1Started,
            this,
            &MainWindow::showLevel1Widget);

    connect(Model::instance,
            &Model::level2Started,
            this,
            &MainWindow::showLevel2Widget);

    connect(Model::instance,
            &Model::level3Started,
            this,
            &MainWindow::showLevel3Widget);

    connect(Model::instance,
            &Model::showLevelComplete,
            this,
            &MainWindow::showSuccessWidget);

    connect(Model::instance,
            &Model::showLevelFailure,
            this,
            &MainWindow::showFailWidget);
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
    ui->carWidget->raise();
}

void MainWindow::showLevel2Widget()
{
    hideAllWidgets();
    ui->level2Widget->show();
    ui->carWidget->show();
    ui->carWidget->raise();
}

void MainWindow::showLevel3Widget()
{
    hideAllWidgets();
    ui->level3Widget->show();
    ui->carWidget->show();
    ui->carWidget->raise();
}

void MainWindow::showLevelSelectWidget()
{
    hideAllWidgets();
    ui->levelSelectWidget->show();
}

void MainWindow::showSuccessWidget()
{
    hideAllWidgets();
    ui->successWidget->show();
}

void MainWindow::showFailWidget()
{
    hideAllWidgets();
    ui->failWidget->show();
}

void MainWindow::hideAllWidgets()
{
    ui->carWidget->hide();
    ui->welcomeWidget->hide();
    ui->levelSelectWidget->hide();
    ui->level1Widget->hide();
    ui->level2Widget->hide();
    ui->level3Widget->hide();
    ui->failWidget->hide();
    ui->successWidget->hide();
}
