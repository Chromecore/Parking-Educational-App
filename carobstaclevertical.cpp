#include "carobstaclevertical.h"
#include "ui_carobstaclevertical.h"
#include <QPainter>
#include <random>
CarObstacleVertical::CarObstacleVertical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarObstacleVertical)
{
    ui->setupUi(this);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    ran = dist6(rng);
}

void CarObstacleVertical::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    std::string route = ":/sprites/Resources/car" + std::to_string(ran) + ".png";
    int width =100, height = 115;
    QPixmap pix(route.data());

    QTransform tr;
    if(ran % 2)
        tr.rotate(90);
    else
        tr.rotate(270);
    pix = pix.transformed(tr);

    painter.drawPixmap(QRect(0, 0, width, height), pix);
    painter.end();
}
CarObstacleVertical::~CarObstacleVertical()
{
    delete ui;
}
