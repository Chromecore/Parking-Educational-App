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

    // Define the ground body.
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, 20.0f);

//    // Call the body factory which allocates memory for the ground body
//    // from a pool and creates the ground box shape (also from a pool).
//    // The body is also added to the world.
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);

//    // Define the ground box shape.
//    b2PolygonShape groundBox;

//    // The extents are the half-widths of the box.
//    groundBox.SetAsBox(50.0f, 10.0f);

//    // Add the ground fixture to the ground body.
//    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    //bodyDef.linearDamping = 0;
    //bodyDef.angularDamping = 0;

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
    //fixtureDef.restitution = 1;
    //fixtureDef.restitution = 0.9;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
    //printf("Init world\n");

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
    QTransform transform;
    transform.rotate(angle);
    //QPoint center = image.rect().center();
    //transform.translate(center.x(), center.y());
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    //ui->carLabel->setPixmap(pixmap);

    //ui->carLabel->setPixmap(pixmap);
    //ui->carLabel->move((int)(position.x*20), (int)(position.x*20));
    //painter.rotate(angle);
    //move((int)(position.x*20), (int)(position.x*20));
    //painter.rotate(angle);
    //painter.drawImage((int)(position.x*20), (int)(position.x*20), image);
    painter.drawPixmap(QRect((int)(position.x*80), (int)(position.y*80), 100, 100), pixmap);
    painter.end();
}

void Car::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
    body->SetAngularVelocity(0);

    // kill side velocity
    float angle = -body->GetAngle() + 180;
    QVector2D up(cos(PI * (180 - angle) / 180), sin(PI * (180 - angle) / 180));
    angle += 90;
    QVector2D right(cos(PI * (180 - angle) / 180), sin(PI * (180 - angle) / 180));
    QVector2D carVelocity(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    //b2Vec2 right(1, 0);
    //float carSpeed = body->GetLinearVelocity().x + body->GetLinearVelocity().y;
    //float carSpeed = sqrt(pow(body->GetLinearVelocity().x, 2) + pow(body->GetLinearVelocity().y, 2));
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
    //body->SetLinearVelocity(direction);

    switch(event->key())
    {
        case Qt::Key_W:
            body->ApplyForceToCenter(direction, true);
            break;
        case Qt::Key_A:
            body->ApplyAngularImpulse(-300.0f, true);
            break;
        case Qt::Key_S:
            body->ApplyForceToCenter(-direction, true);
            break;
        case Qt::Key_D:
            body->ApplyAngularImpulse(300.0f, true);
            break;
        default:
            break;
    }
}
