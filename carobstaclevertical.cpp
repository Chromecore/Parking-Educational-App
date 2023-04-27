/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "carobstaclevertical.h"
#include "ui_carobstaclevertical.h"
#include <QPainter>
#include <random>
CarObstacleVertical::CarObstacleVertical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarObstacleVertical)
{
    ui->setupUi(this);
    //create a directory for a random car image in resources
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    ran = dist6(rng);
    route = ":/sprites/Resources/car" + std::to_string(ran) + ".png";
}

void CarObstacleVertical::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(route.data());
    //turn the original picture 90 degrees
    QTransform tr;
    if(ran % 2)
        tr.rotate(90);
    else
        tr.rotate(270);
    pix = pix.transformed(tr);

    painter.drawPixmap(QRect(0, 0, 100, 115), pix);
    painter.end();
}
CarObstacleVertical::~CarObstacleVertical()
{
    delete ui;
}
