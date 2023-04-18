/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "carmodel.h"
#include "model.h"
#include <QDebug>
#include <QKeyEvent>
#include <vector>
#include "model.h"

#include "yellowlinehitbox.h"

CarModel::CarModel(QObject *parent)
    : QObject{parent},
      world(b2Vec2(0.0f, 0.0f)),
      timer(this),
      image(":/sprites/Resources/car.png")
{
    connect(Model::instance,
            &Model::keyPressed,
            this,
            &CarModel::keyPressed);

    // setup the image
    float size = screenWidth / sqrt(2);
    image = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(4, 4);

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
    connect(&timer, &QTimer::timeout, this, &CarModel::updateWorld);
    timer.start(10);


    //Added for Collision Testing
    body->SetUserData( body );
    world.SetContactListener(&myContactListener);


    //Testing to see if casting works. It does.
    //YellowLineHitbox* testBox = world.CreateBody(&bodyDef);Trying to get the hitbox to be set up like b2Body.
    //Maybe try b2Body testBox = YellowLineHitbox; world.AddBody(?)
    //testBox->CreateFixture(&fixtureDef);
}

void CarModel::updateWorld() {
    // update the world
    world.Step(1.0/60.0, 6, 2);
    emit updateUI();

    //Test for Collision
    if (body->getContactNum() > 0 ){
        qDebug() << "contacting";
    }


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

    // clamp car to screen
    b2Vec2 bodyPosition = body->GetPosition();
    if(bodyPosition.x > drivableAreaWidth / positionScaler){
        bodyPosition.x = drivableAreaWidth / positionScaler;
        zeroOutVelocity();
    }
    else if(bodyPosition.x < 0) {
        bodyPosition.x = 0;
        zeroOutVelocity();
    }
    if(bodyPosition.y > drivableAreaWidth / positionScaler){
        bodyPosition.y = drivableAreaWidth / positionScaler;
        zeroOutVelocity();
    }
    else if(bodyPosition.y < 0) {
        bodyPosition.y = 0;
        zeroOutVelocity();
    }
    setCarPosition(bodyPosition);

    // clamp the car speed at the maximum speed
//    float carSpeed = sqrt(pow(body->GetLinearVelocity().x, 2) + pow(body->GetLinearVelocity().y, 2));
//    if(carSpeed > maxSpeed)
//    {
//        b2Vec2 newClampedSpeed = body->GetLinearVelocity();
//        newClampedSpeed.Normalize();
//        newClampedSpeed.x = newClampedSpeed.x * maxSpeed;
//        newClampedSpeed.y = newClampedSpeed.y * maxSpeed;
//        body->SetLinearVelocity(newClampedSpeed);
//    }
}

void CarModel::keyPressed(QKeyEvent* event)
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
            body->ApplyAngularImpulse(-angularImpulse * angleEffector, true);
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
            if(velocity.x <= breakSpeed && velocity.x >= -breakSpeed) velocity.x = 0;
            if(velocity.y <= breakSpeed && velocity.y >= -breakSpeed) velocity.y = 0;

            body->SetLinearVelocity(velocity);
            break;
        default:
            break;
    }
}

void CarModel::setCarPosition(b2Vec2 newPosition)
{
    body->SetTransform(newPosition, body->GetAngle());
}

void CarModel::setCarAngle(float newAngle)
{
    body->SetTransform(body->GetPosition(), newAngle);
}

void CarModel::zeroOutVelocity()
{
    body->SetLinearVelocity(b2Vec2(0,0));
}

b2Body* CarModel::getCarBody(){
    return body;
}

QImage CarModel::getCarImage(){
    return image;
}

float CarModel::getCarScale(){
    return carScale;
}
