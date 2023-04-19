#include "level5.h"
#include "ui_level5.h"

Level5::Level5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level5)
{
    ui->setupUi(this);
}

Level5::~Level5()
{
    delete ui;
}
