#include "failscreen.h"
#include "ui_failscreen.h"
#include "model.h"

FailScreen::FailScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailScreen)
{
    ui->setupUi(this);
    QPixmap pixmap(":/sprites/Resources/failed.png");
    ui->label->setPixmap(pixmap.scaled(600, 300));
}

FailScreen::~FailScreen()
{
    delete ui;
}

void FailScreen::homeButtonClicked()
{
    Model::instance->goHome();
}
