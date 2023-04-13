#include "failscreen.h"
#include "ui_failscreen.h"

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
