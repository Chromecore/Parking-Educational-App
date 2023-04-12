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

    connect(ui->welcomeWidget,
            &WelcomeScreen::startTutorial,
            this,
            &MainWindow::showLevel1Widget);
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
}

void MainWindow::hideAllWidgets()
{
    ui->carWidget->hide();
    ui->welcomeWidget->hide();
    ui->level1Widget->hide();
}
