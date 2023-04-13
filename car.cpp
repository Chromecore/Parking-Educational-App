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

    // setup the image
    float sqrt2 = sqrt(2);
    float size = width() / sqrt2;
    image = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(startingPosition.x, startingPosition.y);

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

    // start the main update loop
    connect(&timer, &QTimer::timeout, this, &Car::updateWorld);
    timer.start(10);
}

Car::~Car()
{
    delete ui;
}

void Car::paintEvent(QPaintEvent *) {
    // create a painter and get pixmap
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.convertFromImage(image);

    // rotate the car based on the body angle
    float angle = body->GetAngle();
    QTransform transform;
    transform.rotate(angle);
    pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);

    b2Vec2 position = body->GetPosition();
    // scale the car based on rotation to account for growing and shrinking
    // the sin function gives 1 at all diagonal directions and 0 at all cardinal directions
    float scaler = abs(sin(Model::degToRad(angle) * 2)) * scalerAt45Deg + 1;
    // draw the car at its position and scale
    painter.drawPixmap(QRect((int)(position.x*80), (int)(position.y*80), carScale * scaler, carScale * scaler), pixmap);
    painter.end();
}

void Car::updateWorld() {
    // apply angular friction to stop car from continualy rotating
    body->SetAngularVelocity(0);

    // kill side velocity
    float angleRad = Model::degToRad(-body->GetAngle() + 180);
    QVector2D upVector(cos(angleRad), sin(angleRad));
    QVector2D rightVector(cos(angleRad + Model::PI / 2), sin(angleRad  + Model::PI / 2));
    QVector2D carVelocity(body->GetLinearVelocity().x, body->GetLinearVelocity().y);

    QVector2D forwardVelocity = upVector * carVelocity.dotProduct(carVelocity, upVector);
    QVector2D rightVelocity = rightVector * carVelocity.dotProduct(carVelocity, rightVector);

    QVector2D velocity = forwardVelocity + rightVelocity * sideVelocityMultiplyer;

    body->SetLinearVelocity(b2Vec2(velocity.x(), velocity.y()));

    // clamp the car speed at the maximum speed
    float carSpeed = sqrt(pow(body->GetLinearVelocity().x, 2) + pow(body->GetLinearVelocity().y, 2));
    if(carSpeed > maxSpeed)
    {
        b2Vec2 newClampedSpeed = body->GetLinearVelocity();
        newClampedSpeed.Normalize();
        newClampedSpeed.x = newClampedSpeed.x * maxSpeed;
        newClampedSpeed.y = newClampedSpeed.y * maxSpeed;
        body->SetLinearVelocity(newClampedSpeed);
    }

    // update the world
    world.Step(1.0/60.0, 6, 2);
    update();
}

void Car::keyPressed(QKeyEvent* event)
{
    // find the direction the car is facing
    float angleRad = Model::degToRad(-body->GetAngle() + 180);
    b2Vec2 direction(cos(angleRad), sin(angleRad));

    // stop from turning when not moving
    float angleEffector = 0;
    float carSpeed = sqrt(pow(body->GetLinearVelocity().x, 2) + pow(body->GetLinearVelocity().y, 2));
    angleEffector = abs(carSpeed) / 0.6f;

    b2Vec2 velocity = body->GetLinearVelocity();

    // handle the input
    switch(event->key())
    {
        case Qt::Key_W:
            // move forward
            direction.x *= driveSpeed;
            direction.y *= driveSpeed;
            body->ApplyForceToCenter(direction, true);
            break;
        case Qt::Key_A:
            // turn left
            body->ApplyAngularImpulse(angularImpulse * angleEffector, true);
            break;
        case Qt::Key_S:
            // move backwards
            direction.x *= reverseSpeed;
            direction.y *= reverseSpeed;
            body->ApplyForceToCenter(-direction, true);
            break;
        case Qt::Key_D:
            // turn right
            body->ApplyAngularImpulse(angularImpulse * angleEffector, true);
            break;
        case Qt::Key_Space:
            // break
            if(velocity.x > 0) velocity.x -= breakSpeed;
            if(velocity.x < 0) velocity.x += breakSpeed;
            if(velocity.y > 0) velocity.y -= breakSpeed;
            if(velocity.y < 0) velocity.y += breakSpeed;

            // snap to 0 if withing break stopping point
            if(velocity.x <= breakStoppingPoint && velocity.x >= -breakStoppingPoint) velocity.x = 0;
            if(velocity.y <= breakStoppingPoint && velocity.y >= -breakStoppingPoint) velocity.y = 0;

            body->SetLinearVelocity(velocity);
            break;
        default:
            break;
    }
}
