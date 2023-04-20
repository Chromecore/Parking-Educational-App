#include "carobstacle.h"
#include "ui_carobstacle.h"
#include <cstdlib>
#include <QPainter>
#include <QDebug>
using std::string;
CarObstacle::CarObstacle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarObstacle)

{
    ui->setupUi(this);
    std::srand((unsigned) time(NULL));
    ran = std::rand() % 6 + 1;


}

void CarObstacle::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    string route = ":/sprites/Resources/car" + std::to_string(ran) + ".png";
    float size = 800 / sqrt(2);
    //qDebug() << route.data();
    QPixmap pix(route.data());
    painter.drawPixmap(QRect(0, 0, 115, 100), pix);
    painter.end();
}

CarObstacle::~CarObstacle()
{
    delete ui;
}
