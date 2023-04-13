/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "car.h"
#include "ui_car.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <vector>
#include "model.h"

Car::Car(QWidget *parent) : QWidget(parent),
    ui(new Ui::Car)
{
    ui->setupUi(this);

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &Car::homeButtonClicked);

    connect(Model::instance->carModel,
            &CarModel::updateUI,
            this,
            &Car::updateUI);
}

Car::~Car()
{
    delete ui;
}

void Car::paintEvent(QPaintEvent *) {
    // create a painter and get pixmap
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.convertFromImage(Model::instance->carModel->getCarImage());

    // rotate the car based on the body angle
    float angle = Model::instance->carModel->getCarBody()->GetAngle();
    QTransform transform;
    transform.rotate(angle);
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);

    b2Vec2 position = Model::instance->carModel->getCarBody()->GetPosition();
    // scale the car based on rotation to account for growing and shrinking
    // the sin function gives 1 at all diagonal directions and 0 at all cardinal directions
    float scaler = abs(sin(Model::degToRad(angle) * 2)) * Model::instance->carModel->scalerAt45Deg + 1;
    float recenterYOffset = (pixmap.width() * scaler - pixmap.width()) / 2 / 8;
    // draw the car at its position and scale

    // find the direction the car is facing
    float angleRad = Model::degToRad(-Model::instance->carModel->getCarBody()->GetAngle() + 180);
    b2Vec2 direction(cos(angleRad), sin(angleRad));
    //qDebug() << direction.x;
    float recenterXOffset = recenterYOffset - direction.x;

    // --------TODO : Remove--------
    QImage imageFrame(":/sprites/Resources/Frame.png");
    float sqrt2 = sqrt(2);
    float size = width() / sqrt2;
    imageFrame = imageFrame.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapFrame;
    QPixmap pixmapPivot(1,1);
    pixmapPivot.fill(Qt::red);
    pixmapFrame.convertFromImage(imageFrame);
    float carScale = Model::instance->carModel->getCarScale();
    painter.drawPixmap(QRect((int)(position.x*80) - recenterXOffset, (int)(position.y*80) - recenterYOffset, carScale * scaler, carScale * scaler), pixmapFrame);
    // --------------------------------

    painter.drawPixmap(QRect((int)(position.x*80) - recenterXOffset, (int)(position.y*80) - recenterYOffset, carScale * scaler, carScale * scaler), pixmap);

    // TODO : Remove
    painter.drawPixmap(QRect((int)(position.x*80) + width() / 2 / 8, (int)(position.y*80) + width() / 2 / 8, 5, 5), pixmapPivot);

    painter.end();
}

void Car::homeButtonClicked()
{
    Model::instance->goHome();
}

void Car::updateUI(){
    update();
}
