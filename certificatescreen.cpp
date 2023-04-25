#include "certificatescreen.h"
#include "ui_certificatescreen.h"
#include "model.h"

CertificateScreen::CertificateScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CertificateScreen)
{
    ui->setupUi(this);
    QPixmap pixmap(":/sprites/Resources/welldone.png");
    ui->picLabel->setPixmap(pixmap.scaled(600, 200));

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &CertificateScreen::homeButtonClicked);

    connect(Model::instance,
            &Model::showTutorialComplete,
            this,
            &CertificateScreen::showTutorialComplete);
}

CertificateScreen::~CertificateScreen()
{
    delete ui;
}

void CertificateScreen::homeButtonClicked()
{
    Model::instance->goHome();
}

void CertificateScreen::showTutorialComplete(bool allLevelsComplete)
{
    if (allLevelsComplete)
    {
        ui->certificateLabel->show();
        ui->redoLabel->hide();
    }
    else
    {
        ui->redoLabel->show();
        ui->certificateLabel->hide();
    }
}
