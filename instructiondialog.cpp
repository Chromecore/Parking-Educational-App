#include "instructiondialog.h"
#include "ui_instructiondialog.h"
#include <QMovie>

InstructionDialog::InstructionDialog(QWidget *parent, int levelNum) :
    QDialog(parent),
    ui(new Ui::InstructionDialog)
{
    ui->setupUi(this);

    qDebug() << levelNum;

    connect(ui->closeButton,
            &QPushButton::clicked,
            this,
            &InstructionDialog::close);

    switch (levelNum)
    {
        case 1:
            showPerpendicularParkGif();
            break;
        case 2:
            showBackingParkGif();
            break;
        case 3:
            showParallelParkGif();
            break;
        case 4:
            showPerpendicularParkGif();
            break;
        case 5:
            showParallelParkGif();
            break;
        default:
            showParallelParkGif();
            break;

    }

    this->exec();
}

InstructionDialog::~InstructionDialog()
{
    delete ui;
    delete movie;
}

void InstructionDialog::showPerpendicularParkGif()
{
    ui->movieLabel->setFixedSize(250, 130);
    movie = new QMovie(":/sprites/Resources/perpendicularPark.gif");
    movie->setScaledSize(ui->movieLabel->size());
    ui->movieLabel->setMovie(movie);
    movie->start();
}

void InstructionDialog::showBackingParkGif()
{
    ui->movieLabel->setFixedSize(250, 130);
    movie = new QMovie(":/sprites/Resources/backingPark.gif");
    movie->setScaledSize(ui->movieLabel->size());
    ui->movieLabel->setMovie(movie);
    movie->start();
}

void InstructionDialog::showParallelParkGif()
{
    ui->movieLabel->setFixedSize(250, 130);
    movie = new QMovie(":/sprites/Resources/parallelPark.gif");
    movie->setScaledSize(ui->movieLabel->size());
    ui->movieLabel->setMovie(movie);
    movie->start();
}
