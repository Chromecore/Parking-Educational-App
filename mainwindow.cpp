/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include "welcomescreen.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(Model::instance,
            &Model::runningLevelSelect,
            this,
            &MainWindow::showLevelSelectWidget);

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
            &Model::level4Started,
            this,
            &MainWindow::showLevel4Widget);

    connect(Model::instance,
            &Model::level5Started,
            this,
            &MainWindow::showLevel5Widget);

    connect(Model::instance,
            &Model::showLevelComplete,
            this,
            &MainWindow::showSuccessWidget);

    connect(Model::instance,
            &Model::showLevelFailure,
            this,
            &MainWindow::showFailWidget);

    connect(Model::instance,
            &Model::showTutorialComplete,
            this,
            &MainWindow::showCertificateWidget);

    Model::instance->goHome();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->isAutoRepeat() || !Model::instance->canDrive) return;
    emit Model::instance->keyPressed(event);
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat() || !Model::instance->canDrive) return;
    emit Model::instance->keyRelease(event);
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::showWelcomeWidget()
{
    hideAllWidgets();
    ui->welcomeWidget->show();
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

void MainWindow::showLevel4Widget()
{
    hideAllWidgets();
    ui->level4Widget->show();
    ui->carWidget->show();
    ui->carWidget->raise();
}

void MainWindow::showLevel5Widget()
{
    hideAllWidgets();
    ui->level5Widget->show();
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
    ui->successWidget->show();
    ui->successWidget->raise();
}

void MainWindow::showFailWidget()
{
    ui->failWidget->show();
    ui->failWidget->raise();
}

void MainWindow::showCertificateWidget(bool tutorialComplete)
{
    hideAllWidgets();
    ui->certificateWidget->show();
}

void MainWindow::hideAllWidgets()
{
    ui->carWidget->hide();
    ui->welcomeWidget->hide();
    ui->levelSelectWidget->hide();
    ui->level1Widget->hide();
    ui->level2Widget->hide();
    ui->level3Widget->hide();
    ui->level4Widget->hide();
    ui->level5Widget->hide();
    ui->failWidget->hide();
    ui->successWidget->hide();
    ui->certificateWidget->hide();
}
