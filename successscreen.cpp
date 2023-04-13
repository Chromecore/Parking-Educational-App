#include "successscreen.h"
#include "ui_successscreen.h"
#include "model.h"

SuccessScreen::SuccessScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuccessScreen)
{
    ui->setupUi(this);
}

SuccessScreen::~SuccessScreen()
{
    delete ui;
}

void SuccessScreen::homeButtonClicked()
{
    Model::instance->goHome();
}
