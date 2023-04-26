#include "carobstacle.h"
#include "ui_carobstacle.h"
#include <QPainter>
#include <random>
using std::string;
CarObstacle::CarObstacle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarObstacle)

{
    ui->setupUi(this);
    //create a directory for a random car image in resources
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    int ran = dist6(rng);
    route = ":/sprites/Resources/car" + std::to_string(ran) + ".png";
}

void CarObstacle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(route.data());
    painter.drawPixmap(QRect(0, 0, 115, 100), pix);
    painter.end();
}

CarObstacle::~CarObstacle()
{
    delete ui;
}
