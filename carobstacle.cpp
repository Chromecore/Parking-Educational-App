#include "carobstacle.h"
#include "ui_carobstacle.h"
#include <cstdlib>
using std::string;
CarObstacle::CarObstacle(QWidget *parent) :
    QWidget(parent),
    image(""),
    ui(new Ui::CarObstacle)

{
    ui->setupUi(this);
    std::srand((unsigned) time(NULL));
    int ran = std::rand() % 6 + 1;

    string route = ":/sprites/Resources/car" + std::to_string(ran) + ".png";
    float size = 800 / sqrt(2);
    image = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //image.load(route);
}

CarObstacle::~CarObstacle()
{
    delete ui;
}
