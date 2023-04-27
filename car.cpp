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

    connect(Model::instance->carModel,
            &CarModel::updateUI,
            this,
            &Car::updateUI);
}

Car::~Car()
{
    delete ui;
}

void Car::paintEvent(QPaintEvent *)
{
    // create a painter and get pixmap
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.convertFromImage(Model::instance->carModel->getCarImage());

    float angle = Model::instance->carModel->getCarBody()->GetAngle();

    // rotate the car around a pivot
    QPointF offset;
    pixmap = rotatePixmap(pixmap, QPoint(5, 0), Model::degToRad(-angle + 180), offset);

    // get the position to draw the car on the UI
    b2Vec2 position = Model::instance->carModel->getCarBody()->GetPosition();
    float positionScaler = Model::instance->carModel->positionScaler;
    float x = position.x * positionScaler + offset.x();
    float y = position.y * positionScaler + offset.y();

    // scale the car based on rotation to account for growing and shrinking
    // the sin function gives 1 at all diagonal directions and 0 at all cardinal directions
    float scaler = abs(sin(Model::degToRad(angle) * 2)) * Model::instance->carModel->scalerAt45Deg + 1;
    float carScale = Model::instance->carModel->getCarScale();
    float scale = carScale * scaler;

    // move the car ui position to align with the car body position
    b2Body* body = Model::instance->carModel->getCarBody();
    float differenceX = x + scale / 2 - body->GetPosition().x * positionScaler;
    float differenceY= y + scale / 2 - body->GetPosition().y * positionScaler;
    x -= differenceX;
    y -= differenceY;

    // draw the car
    painter.drawPixmap(QRect(x, y, scale, scale), pixmap);
    painter.end();

    if(shouldDrawGizmos) drawGizmos(x, y, scale);
}

void Car::drawGizmos(float x, float y, float scale)
{
    // draw a gizmo frame around the car that does not rotate
    QPainter painter(this);
    QImage imageFrame(":/sprites/Resources/Frame.png");
    float sqrt2 = sqrt(2);
    float size = width() / sqrt2;
    imageFrame = imageFrame.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap pixmapFrame;
    pixmapFrame.convertFromImage(imageFrame);
    painter.drawPixmap(QRect(x, y, scale, scale), pixmapFrame);

    // draw a gizmo frame around the car that does rotate
    QPointF offset;
    float angle = Model::instance->carModel->getCarBody()->GetAngle();
    pixmapFrame = rotatePixmap(pixmapFrame, QPoint(5, 0), Model::degToRad(-angle + 180), offset);
    painter.drawPixmap(QRect(x, y, scale, scale), pixmapFrame);

    // draw car body center
    QPixmap centerPixmap(10,10);
    centerPixmap.fill(Qt::blue);
    float bodyX = Model::instance->carModel->getCarBody()->GetPosition().x * Model::instance->carModel->positionScaler;
    float bodyY = Model::instance->carModel->getCarBody()->GetPosition().y * Model::instance->carModel->positionScaler;
    painter.drawPixmap(bodyX, bodyY, centerPixmap);
    painter.end();
}

QPixmap Car::rotatePixmap(QPixmap pixmap, QPointF pivot, qreal angle, QPointF &offset)
{
    QPointF center = QPointF(pixmap.width() / 2 / 8, pixmap.height() / 2 / 8);
    qreal distance = QLineF(pivot, center).length();
    qreal a = atan2(pivot.y() - center.y(), pivot.x() - center.x());
    QPointF rotationPivot(cos(angle + a) * distance, sin(angle + a) * distance);
    rotationPivot += center;

    QPixmap rotationImage = pixmap.transformed(QTransform().rotateRadians(angle), Qt::SmoothTransformation);

    QPointF rotationCenter = QPointF(rotationImage.width() / 2 / 8, rotationImage.height() / 2 / 8);
    QPointF rotationOffset = rotationCenter - center;

    offset = -rotationPivot - rotationOffset;

    return rotationImage;
}

void Car::updateUI()
{
    update();
}
