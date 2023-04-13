#include "failscreen.h"
#include "ui_failscreen.h"
#include "model.h"

FailScreen::FailScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailScreen)
{
    ui->setupUi(this);
}

FailScreen::~FailScreen()
{
    delete ui;
}

void FailScreen::homeButtonClicked()
{
    Model::instance->goHome();
}
