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

CarModel::CarModel(QObject *parent)
    : QObject{parent},
      world(b2Vec2(0.0f, 0.0f)),
      timer(this),
      image("")
{
    connect(Model::instance,
            &Model::keyPressed,
            this,
            &CarModel::keyPressed);

    connect(Model::instance,
            &Model::keyRelease,
            this,
            &CarModel::keyRelease);


    setupCar();
    //setupColliders();

    // start the main update loop
    connect(&timer, &QTimer::timeout, this, &CarModel::updateWorld);
    timer.start(10);


}

void CarModel::setupCar()
{
    loadCar();

    // setup the image
    float size = screenWidth / sqrt(2);
    image = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    hitBoxImage = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // sets up all body definitions and fixtures for hitboxes. 0 is driveable car,
    // 1 is the goal hitbox, 2 is the not intangible hitbox (think yellow lines)
    // 3 is tangible hitboxes (think parked cars)

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef driveableCarBodyDef;
    b2BodyDef goalBodyDef;
    b2BodyDef hazardBodyDef;
    b2BodyDef parkedCarBodyDef;

    driveableCarBodyDef.type = b2_dynamicBody;
    goalBodyDef.type = b2_staticBody;
    hazardBodyDef.type = b2_staticBody;
    parkedCarBodyDef.type = b2_staticBody;

    driveableCarBodyDef.position.Set(4, 4);
    goalBodyDef.position.Set(1, 1);
    hazardBodyDef.position.Set(2, 1);
    parkedCarBodyDef.position.Set(3, 1);

    // Define another box shape for our dynamic body.
    b2PolygonShape driveableCarBox;
    driveableCarBox.SetAsBox(1.0f, 1.0f);
    b2PolygonShape otherHitboxShape;
    otherHitboxShape.SetAsBox(1.0f, 1.0f * 9/20);


    // Define the dynamic body fixture.
    b2FixtureDef driveableCarFixtureDef;
    driveableCarFixtureDef.shape = &driveableCarBox;
    b2FixtureDef goalFixtureDef;
    goalFixtureDef.shape = &otherHitboxShape;
    b2FixtureDef hazardFixtureDef;
    hazardFixtureDef.shape = &otherHitboxShape;
    b2FixtureDef parkedCarFixtureDef;
    parkedCarFixtureDef.shape = &otherHitboxShape;

    //for goal and hazard fixtures, they need to be declared as sensors.
    goalFixtureDef.isSensor = true;
    hazardFixtureDef.isSensor = true;
    // goalFixtureDef.filter.categoryBits = HAZARD_HITBOX;
    // goalFixtureDef.filter.maskBits = DRIVEABLE_CAR_HITBOX;

    // Set the box density to be non-zero, so it will be dynamic.
    driveableCarFixtureDef.density = 1.0f;
    goalFixtureDef.density = 1.0f;
    hazardFixtureDef.density = 1.0f;
    parkedCarFixtureDef.density = 1.0f;

    // Override the default friction.
    driveableCarFixtureDef.friction = 1.0f;
    goalFixtureDef.friction = 1.0f;
    hazardFixtureDef.friction = 1.0f;
    parkedCarFixtureDef.friction = 1.0f;


    //assign car's body.
    body = world.CreateBody(&driveableCarBodyDef);
    body ->setFailedPark(false);

    // Add the shape to the body.
    body->CreateFixture(&driveableCarFixtureDef);

    setCarAngle(0);

    // start the main update loop
    connect(&timer, &QTimer::timeout, this, &CarModel::updateWorld);
    timer.start(10);

    // set up Collision Testing
    body->SetUserData( body );
    world.SetContactListener(&myContactListener);
    isParkedSuccessfully = false;

    //Creation of all the hitboxes.

    //Main center fail hitbox that fails the player if they haven't left center.
    //Steps to creating a new hitbox.
    otherHitboxShape.SetAsBox(1.0f * 1.45, 1.0f * 5);
    hazardBodyDef.position.Set(3, 1);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* centerHazardHitbox = world.CreateBody(&hazardBodyDef);
    centerHazardHitbox->setHitboxType(2);
    centerHazardHitbox->CreateFixture(&hazardFixtureDef);


    //Parked Car hitbox 1. //Good
    otherHitboxShape.SetAsBox(1.0f * 2/3, 1.0f * 1/2);
    parkedCarBodyDef.position.Set(6.4, 3.3);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar1 = world.CreateBody(&parkedCarBodyDef);
    parkedCar1->setHitboxType(3);
    parkedCar1->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 2. //BUGGY
    otherHitboxShape.SetAsBox(1.0f * 2/3, 1.0f * 1/3);
    parkedCarBodyDef.position.Set(6.4, 5.72);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar2 = world.CreateBody(&parkedCarBodyDef);
    parkedCar2->setHitboxType(3);
    parkedCar2->CreateFixture(&parkedCarFixtureDef);


    //Goal Hitbox Right Side. //Good
    otherHitboxShape.SetAsBox(1.0f, 1.0f * 10);
    goalBodyDef.position.Set(7.9, 0);
    goalFixtureDef.shape = &otherHitboxShape;
    b2Body* rightmostGoalHitbox = world.CreateBody(&goalBodyDef);
    rightmostGoalHitbox->setHitboxType(1);
    rightmostGoalHitbox->CreateFixture(& goalFixtureDef);


    //Goal Hitbox Left Side. //Good
    otherHitboxShape.SetAsBox(1.0f * 1/3, 1.0f * 10);
    goalBodyDef.position.Set(0, 0);
    goalFixtureDef.shape = &otherHitboxShape;
    b2Body* leftmostGoalHitbox = world.CreateBody(&goalBodyDef);
    leftmostGoalHitbox->setHitboxType(1);
    leftmostGoalHitbox->CreateFixture(& goalFixtureDef);

    //Hazard hitbox left 1. // Needs work.
    otherHitboxShape.SetAsBox(1.0f, 0.001);
    hazardBodyDef.position.Set(0, 1.0f * 1.67);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* leftHazard1Hitbox = world.CreateBody(&hazardBodyDef);
    leftHazard1Hitbox->setHitboxType(2);
    leftHazard1Hitbox->CreateFixture(&hazardFixtureDef);


    //Hazard hitbox left 2. // Needs work
    otherHitboxShape.SetAsBox(1.0f, 0.001);
    hazardBodyDef.position.Set(0, 1.0f * 3.35);
    hazardFixtureDef.shape = &otherHitboxShape;
    testHitbox = world.CreateBody(&hazardBodyDef);
    testHitbox->setHitboxType(2);
    testHitbox->CreateFixture(&hazardFixtureDef);

    //testHitbox = world.CreateBody(&bodyDefHazard);
    //testHitbox->setHitboxType(2);
    //testHitbox->CreateFixture(&fixtureDefHitbox);
}

void CarModel::updateWorld()
{
    // update the world
    world.Step(1.0/60.0, 6, 2);
    emit updateUI();

    // update the car
    handleCollisions();
    handleDrifting();
    clampCarPosition();
    applyInput();
    clampCarSpeed();
}

void CarModel::handleCollisions()
{
    // win condition
    if (body->getHazardContactNum() > 0 ){
        //qDebug() << "LOSE";
        isParkedSuccessfully = false;
    }
    else if (body->getGoalContactNum() > 0){
        qDebug() << "WIN";
        isParkedSuccessfully = true;
    }

    // check if collided with obstacle that causes automatic fail
    if (body->getFailedPark()){
        Model::instance->failedPark();
    }

}

void CarModel::handleDrifting()
{
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
}

void CarModel::clampCarPosition()
{
    float angleRad = Model::degToRad(-body->GetAngle() + 180);
    b2Vec2 bodyPosition = body->GetPosition();
    // change the car position so the car collides with the boundries at the center of the car instead of the edge
    b2Vec2 direction(cos(angleRad), sin(angleRad));
    direction.x *= 0.25;
    direction.y *= 0.25;
    bodyPosition += direction;
    // clamp right side
    if(bodyPosition.x > (drivableAreaWidth - carScale) / positionScaler + 1)
    {
        bodyPosition.x = (drivableAreaWidth - carScale) / positionScaler + 1;
        zeroOutVelocity();
    }
    // clamp left side
    else if(bodyPosition.x < 0)
    {
        bodyPosition.x = 0;
        zeroOutVelocity();
    }
    // clamp bottom
    if(bodyPosition.y > (drivableAreaWidth - carScale) / positionScaler + 1)
    {
        bodyPosition.y = (drivableAreaWidth - carScale) / positionScaler + 1;
        zeroOutVelocity();
    }
    // clamp top
    else if(bodyPosition.y < 0)
    {
        bodyPosition.y = 0;
        zeroOutVelocity();
    }
    bodyPosition -= direction;
    setCarPosition(bodyPosition);
}

void CarModel::clampCarSpeed()
{
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
}

void CarModel::keyPressed(QKeyEvent* event)
{
    // record key presses
    int key = event->key();
    if(key == driveKey) drivePressed = true;
    if(key == leftKey) leftPressed = true;
    if(key == reverseKey) reversePressed = true;
    if(key == rightKey) rightPressed = true;
    if(key == breakKey) breakPressed = true;

    // TODO : Temp Remove
    if(key == Qt::Key_P) loadCar();
    if(key == Qt::Key_O) loadTruck();
}

void CarModel::keyRelease(QKeyEvent* event)
{
    // record key releases
    int key = event->key();
    if(key == driveKey) drivePressed = false;
    if(key == leftKey) leftPressed = false;
    if(key == reverseKey) reversePressed = false;
    if(key == rightKey) rightPressed = false;
    if(key == breakKey) breakPressed = false;
}

void CarModel::applyInput()
{
    // find the direction the car is facing
    float angleRad = Model::degToRad(-body->GetAngle() + 180);
    b2Vec2 direction(cos(angleRad), sin(angleRad));

    // stop from turning when not moving
    float angleEffector = 0;
    float carSpeed = sqrt(pow(body->GetLinearVelocity().x, 2) + pow(body->GetLinearVelocity().y, 2));
    angleEffector = carSpeed / turnDriveRelationship;

    b2Vec2 velocity = body->GetLinearVelocity();

    // apply the input
    if(drivePressed)
    {
        // move forward
        direction.x *= driveSpeed;
        direction.y *= driveSpeed;
        body->ApplyForceToCenter(direction, true);
    }
    if(leftPressed)
    {
        // turn left
        body->ApplyAngularImpulse(-angularImpulse * angleEffector, true);
    }
    if(reversePressed)
    {
        // move backwards
        direction.x *= reverseSpeed;
        direction.y *= reverseSpeed;
        body->ApplyForceToCenter(-direction, true);
    }
    if(rightPressed)
    {
        // turn right
        body->ApplyAngularImpulse(angularImpulse * angleEffector, true);
    }
    if(breakPressed)
    {
        // break
        if(velocity.x > 0) velocity.x -= breakSpeed;
        if(velocity.x < 0) velocity.x += breakSpeed;
        if(velocity.y > 0) velocity.y -= breakSpeed;
        if(velocity.y < 0) velocity.y += breakSpeed;

        // snap to 0 if withing break stopping point
        if(velocity.x <= breakSpeed && velocity.x >= -breakSpeed) velocity.x = 0;
        if(velocity.y <= breakSpeed && velocity.y >= -breakSpeed) velocity.y = 0;

        body->SetLinearVelocity(velocity);
    }
}

void CarModel::setCarPosition(b2Vec2 newPosition)
{
    body->SetTransform(newPosition, body->GetAngle());
}

void CarModel::setCarAngle(float newAngle)
{
    // offset to face up at 0 degrees
    newAngle -= 90;
    body->SetTransform(body->GetPosition(), newAngle);
}

void CarModel::zeroOutVelocity()
{
    body->SetLinearVelocity(b2Vec2(0,0));
}

b2Body* CarModel::getCarBody(){
    return body;
}


b2Body* CarModel::getTestHitbox(){
    return testHitbox;
}

QImage CarModel::getCarImage(){
    return image;
}

QImage CarModel::getHitboxImage(){
    return hitBoxImage;
}


float CarModel::getCarScale(){
    return carScale;
}

void CarModel::loadCar()
{
    // load the car sprite along with the car specific variables
    image.load(":/sprites/Resources/car2.png");
    hitBoxImage.load(":/sprites/Resources/Frame.png");
    carScale = 100;
    maxSpeed = 0.8f;
    breakSpeed = 0.04f;
    angularImpulse = 300;
    driveSpeed = 1;
    reverseSpeed = 1;
    sideVelocityMultiplyer = 0.2;
    turnDriveRelationship = 2;
}
void CarModel::loadTruck()
{
    // load the truck sprite along with the truck specific variables
    image.load(":/sprites/Resources/Truck.png");
    carScale = 150;
    maxSpeed = 0.7f;
    breakSpeed = 0.03f;
    angularImpulse = 250;
    driveSpeed = 0.8;
    reverseSpeed = 0.8;
    sideVelocityMultiplyer = 0.1;
    turnDriveRelationship = 2.5;
}

