#include "failscreen.h"
#include "ui_failscreen.h"
#include "model.h"

FailScreen::FailScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailScreen)
{
    ui->setupUi(this);
    QPixmap pixmap(":/sprites/Resources/failed.png");
    ui->label->setPixmap(pixmap.scaled(400, 400));

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &FailScreen::homeButtonClicked);
}

FailScreen::~FailScreen()
{
    delete ui;
}

void FailScreen::homeButtonClicked()
{
    Model::instance->goHome();
}
