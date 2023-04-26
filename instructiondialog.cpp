#include "instructiondialog.h"
#include "ui_instructiondialog.h"
#include <QMovie>
#include "model.h"

InstructionDialog::InstructionDialog(QWidget *parent, int levelNum) :
    QDialog(parent),
    ui(new Ui::InstructionDialog)
{
    ui->setupUi(this);
    hideControls();
    ui->prevButton->setDisabled(true);

    connect(ui->controlsButton,
            &QPushButton::clicked,
            this,
            &InstructionDialog::showControls);

    connect(ui->backButton,
            &QPushButton::clicked,
            this,
            &InstructionDialog::hideControls);

    connect(ui->prevButton,
            &QPushButton::clicked,
            this,
            &InstructionDialog::previousStep);

    connect(ui->nextButton,
            &QPushButton::clicked,
            this,
            &InstructionDialog::nextStep);

    switch (levelNum)
    {
        case 1:
            instructions = Model::instance->dialog[0];
            showPerpendicularTips();
            break;
        case 2:
            instructions = Model::instance->dialog[1];
            showBackingTips();
            break;
        case 3:
            instructions = Model::instance->dialog[2];
            showParallelTips();
            break;
        case 4:
            instructions = Model::instance->dialog[0];
            showPerpendicularTips();
            break;
        case 5:
            instructions = Model::instance->dialog[2];
            showParallelTips();
            break;
        default:
            instructions = Model::instance->dialog[2];
            showParallelTips();
            break;

    }

    stepIndex = 0;

    this->exec();
}

InstructionDialog::~InstructionDialog()
{
    delete ui;
    delete movie;
}

void InstructionDialog::showControls()
{
    ui->movieLabel->hide();
    ui->titleLabel->hide();
    ui->stepLabel->hide();
    ui->controlsButton->hide();
    ui->prevButton->hide();
    ui->nextButton->hide();

    ui->controlsLabel->show();
    ui->backButton->show();
}

void InstructionDialog::hideControls()
{
    ui->controlsLabel->hide();
    ui->backButton->hide();

    ui->movieLabel->show();
    ui->titleLabel->show();
    ui->stepLabel->show();
    ui->controlsButton->show();
    ui->prevButton->show();
    ui->nextButton->show();
}

void InstructionDialog::showPerpendicularTips()
{
    hideControls();

    movie = new QMovie(":/sprites/Resources/perpendicularPark.gif");
    movie->setScaledSize(ui->movieLabel->size());
    ui->movieLabel->setMovie(movie);
    movie->start();

    ui->titleLabel->setText("How To Perpendicular Park");
    ui->stepLabel->setText(instructions[0]);
}

void InstructionDialog::showBackingTips()
{
    hideControls();

    movie = new QMovie(":/sprites/Resources/backingPark.gif");
    movie->setScaledSize(ui->movieLabel->size());
    ui->movieLabel->setMovie(movie);
    movie->start();

    ui->titleLabel->setText("How To Back Into a Space");
    ui->stepLabel->setText(instructions[0]);
}

void InstructionDialog::showParallelTips()
{
    hideControls();

    movie = new QMovie(":/sprites/Resources/parallelPark.gif");
    movie->setScaledSize(ui->movieLabel->size());
    ui->movieLabel->setMovie(movie);
    movie->start();

    ui->titleLabel->setText("How To Parallel Park");
    ui->stepLabel->setText(instructions[0]);
}

void InstructionDialog::previousStep()
{
    if (stepIndex <= 0)
        return;

    ui->stepLabel->setText(instructions[--stepIndex]);

    ui->nextButton->setEnabled(true);
    if (stepIndex == 0)
        ui->prevButton->setDisabled(true);
}

void InstructionDialog::nextStep()
{
    if (stepIndex >= (int)instructions.size() - 1)
        return;

    ui->stepLabel->setText(instructions[++stepIndex]);

    ui->prevButton->setEnabled(true);
    if (stepIndex == (int)instructions.size() - 1)
        ui->nextButton->setDisabled(true);
}
