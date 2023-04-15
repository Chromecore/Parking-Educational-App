#include "successscreen.h"
#include "ui_successscreen.h"
#include "model.h"

SuccessScreen::SuccessScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuccessScreen)
{
    ui->setupUi(this);
    QPixmap pixmap(":/sprites/Resources/passed.png");
    ui->label->setPixmap(pixmap.scaled(600, 600));
}

SuccessScreen::~SuccessScreen()
{
    delete ui;
}

void SuccessScreen::homeButtonClicked()
{
    Model::instance->goHome();
}
