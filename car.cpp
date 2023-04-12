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
    ui(new Ui::Car),
    world(b2Vec2(0.0f, 0.0f)),
    timer(this),
    image(":/sprites/Resources/car.png")
{
    ui->setupUi(this);

    connect(Model::instance,
                &Model::keyPressed,
                this,
                &Car::keyPressed);

    float sqrt2 = sqrt(2);
    float size = width() / sqrt2;
    image = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    PI = acos(-1.0);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 1.0f;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    connect(&timer, &QTimer::timeout, this, &Car::updateWorld);
    timer.start(10);
}

Car::~Car()
{
    delete ui;
}

void Car::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    QPixmap pixmap;
    pixmap.convertFromImage(image);

    //rotate
    float scaler = abs(sin(PI * (180 - angle) / 180 * 2)) * 0.35 + 1;
    QTransform transform;
    transform.rotate(angle);
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);

    // draw
    painter.drawPixmap(QRect((int)(position.x*80), (int)(position.y*80), 100 * scaler, 100 * scaler), pixmap);
    painter.end();
}

void Car::updateWorld() {
    world.Step(1.0/60.0, 6, 2);
    update();
    body->SetAngularVelocity(0);

    // kill side velocity
    float angle = -body->GetAngle() + 180;
    QVector2D up(cos(PI * (180 - angle) / 180), sin(PI * (180 - angle) / 180));
    angle += 90;
    QVector2D right(cos(PI * (180 - angle) / 180), sin(PI * (180 - angle) / 180));
    QVector2D carVelocity(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    QVector2D forwardVelocity = up * carVelocity.dotProduct(carVelocity, up);
    QVector2D rightVelocity = right * carVelocity.dotProduct(carVelocity, right);
    QVector2D velocity = forwardVelocity + rightVelocity * 0;
    b2Vec2 boxVelocity(velocity.x(), velocity.y());
    body->SetLinearVelocity(boxVelocity);
}

void Car::keyPressed(QKeyEvent* event)
{
    float angle = -body->GetAngle() + 180;
    b2Vec2 direction(cos(PI * (180 - angle) / 180), sin(PI * (180 - angle) / 180));
    direction.x *= 1.0f;
    direction.y *= 1.0f;

    // stop from turning when not moving
    float angleEffector = 0;
    float carSpeed = sqrt(pow(body->GetLinearVelocity().x, 2) + pow(body->GetLinearVelocity().y, 2));
    angleEffector = abs(carSpeed) / 0.6f;

    b2Vec2 velocity = body->GetLinearVelocity();

    switch(event->key())
    {
        case Qt::Key_W:
            body->ApplyForceToCenter(direction, true);
            break;
        case Qt::Key_A:
            body->ApplyAngularImpulse(-300.0f * angleEffector, true);
            break;
        case Qt::Key_S:
            body->ApplyForceToCenter(-direction, true);
            break;
        case Qt::Key_D:
            body->ApplyAngularImpulse(300.0f * angleEffector, true);
            break;
        case Qt::Key_Space:
            // break
            qDebug() << velocity.x;
            if(velocity.x > 0) velocity.x -= 0.01f;
            if(velocity.x < 0) velocity.x += 0.01f;
            if(velocity.y > 0) velocity.y -= 0.01f;
            if(velocity.y < 0) velocity.y += 0.01f;
            body->SetLinearVelocity(velocity);
            break;
        default:
            break;
    }

    // max car speed
//    if(carSpeed > 0.6f){
//        b2Vec2 newClmapedSpeed = body->GetLinearVelocity();
//        newClmapedSpeed.Normalize();
//        newClmapedSpeed.x = newClmapedSpeed.x * 0.6f;
//        newClmapedSpeed.y = newClmapedSpeed.y * 0.6f;
//        body->SetLinearVelocity(newClmapedSpeed);
//    }
}
