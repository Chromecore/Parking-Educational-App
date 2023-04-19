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
}

CertificateScreen::~CertificateScreen()
{
    delete ui;
}

void CertificateScreen::homeButtonClicked()
{
    Model::instance->goHome();
}
