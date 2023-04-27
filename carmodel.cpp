/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "carmodel.h"
#include "model.h"
#include <QKeyEvent>
#include <vector>

CarModel::CarModel(QObject *parent)
    : QObject{parent},
      world(b2Vec2(0.0f, 0.0f)),
      timer(this),
      image(":/sprites/Resources/car2.png")
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
    setupColliders();

    gameLevel = 0;
    // start the main update loop
    connect(&timer, &QTimer::timeout, this, &CarModel::updateWorld);
    timer.start(10);
}

void CarModel::setupCar()
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef driveableCarBodyDef;
    driveableCarBodyDef.type = b2_dynamicBody;
    driveableCarBodyDef.position.Set(4, 4);

    // assign car's body.
    body = world.CreateBody(&driveableCarBodyDef);
    body ->setFailedPark(false);

    setCarAngle(0);

    // start the main update loop
    connect(&timer, &QTimer::timeout, this, &CarModel::updateWorld);
    timer.start(10);


    // setup the car
    loadCar();
    float size = screenWidth / sqrt(2);
    image = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void CarModel::setupColliders()
{
    // sets up all body definitions and fixtures for hitboxes. 0 is driveable car,
    // 1 is the goal hitbox, 2 is the not intangible hitbox (think yellow lines)
    // 3 is tangible hitboxes (think parked cars)

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef goalBodyDef;
    b2BodyDef hazardBodyDef;

    goalBodyDef.type = b2_staticBody;
    hazardBodyDef.type = b2_staticBody;

    goalBodyDef.position.Set(1, 1);
    hazardBodyDef.position.Set(2, 1);

    // Define another box shape for our dynamic body.
    b2PolygonShape otherHitboxShape;
    otherHitboxShape.SetAsBox(1.0f, 1.0f * 9/20);

    // Define the dynamic body fixture.
    b2FixtureDef goalFixtureDef;
    goalFixtureDef.shape = &otherHitboxShape;
    b2FixtureDef hazardFixtureDef;
    hazardFixtureDef.shape = &otherHitboxShape;

    //for goal and hazard fixtures, they need to be declared as sensors.
    goalFixtureDef.isSensor = true;
    hazardFixtureDef.isSensor = true;

    // Set the box density to be non-zero, so it will be dynamic.
    goalFixtureDef.density = 1.0f;
    hazardFixtureDef.density = 1.0f;

    // Override the default friction.
    goalFixtureDef.friction = 1.0f;
    hazardFixtureDef.friction = 1.0f;

    // set up Collision Testing
    body->SetUserData( body );
    world.SetContactListener(&myContactListener);
    isParkedSuccessfully = false;

    //Creation of all the hitboxes.
    //Main center fail hitbox that fails the player if they haven't left center.
    //Steps to creating a new hitbox.
    otherHitboxShape.SetAsBox(1.0f * 1.7, 1.0f * 8);
    hazardBodyDef.position.Set(3.4, 0);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* centerHazardHitbox= world.CreateBody(&hazardBodyDef);
    centerHazardHitbox->setHitboxType(2);
    centerHazardHitbox->CreateFixture(&hazardFixtureDef);

    //Goal Hitbox Right Side.
    otherHitboxShape.SetAsBox(1.0f, 1.0f * 10);
    goalBodyDef.position.Set(7, 0);
    goalFixtureDef.shape = &otherHitboxShape;
    b2Body* rightmostGoalHitbox = world.CreateBody(&goalBodyDef);
    rightmostGoalHitbox->setHitboxType(1);
    rightmostGoalHitbox->CreateFixture(& goalFixtureDef);

    //Hazard hitbox right 1.
    otherHitboxShape.SetAsBox(1.0f * 3, 0.02f);
    hazardBodyDef.position.Set(5.8f, 0.84f);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* rightHazard1Hitbox = world.CreateBody(&hazardBodyDef);
    rightHazard1Hitbox->setHitboxType(2);
    rightHazard1Hitbox->CreateFixture(&hazardFixtureDef);

    //Hazard hitbox right 2.
    otherHitboxShape.SetAsBox(1.0f * 3, 0.02f);
    hazardBodyDef.position.Set(5.8f, 0.75f * 2);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* rightHazard2Hitbox = world.CreateBody(&hazardBodyDef);
    rightHazard2Hitbox->setHitboxType(2);
    rightHazard2Hitbox->CreateFixture(&hazardFixtureDef);

    //Hazard hitbox right 3.
    otherHitboxShape.SetAsBox(1.0f * 3, 0.02f);
    hazardBodyDef.position.Set(5.8f, 0.84f * 7.8f);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* rightHazard3Hitbox = world.CreateBody(&hazardBodyDef);
    rightHazard3Hitbox->setHitboxType(2);
    rightHazard3Hitbox->CreateFixture(&hazardFixtureDef);
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
        isParkedSuccessfully = false;
    }
    else if (body->getGoalContactNum() > 0 && body->GetLinearVelocity().x == 0 && body->GetLinearVelocity().y == 0){
        isParkedSuccessfully = true;
    }

    // check if collided with obstacle that causes automatic fail
    if (body->getFailedPark() && Model::instance->canDrive){
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
    if(bodyPosition.x > (drivableAreaWidth - carScale) / positionScaler + carScale / 100)
    {
        bodyPosition.x = (drivableAreaWidth - carScale) / positionScaler + carScale / 100;
        zeroOutVelocity();
    }
    // clamp left side
    else if(bodyPosition.x < 0)
    {
        bodyPosition.x = 0;
        zeroOutVelocity();
    }
    // clamp bottom
    if(bodyPosition.y > (drivableAreaWidth - carScale) / positionScaler + carScale / 100)
    {
        bodyPosition.y = (drivableAreaWidth - carScale) / positionScaler + carScale / 100;
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

    // handle the inverted turn when going backwards
    QVector2D velVec(velocity.x, velocity.y);
    QVector2D dirVec(direction.x, direction.y);
    float invertTurn = velVec.dotProduct(velVec, dirVec);

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
        body->ApplyAngularImpulse(-angularImpulse * angleEffector * invertTurn, true);
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
        body->ApplyAngularImpulse(angularImpulse * angleEffector * invertTurn, true);
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
    drivePressed = false;
    leftPressed = false;
    reversePressed = false;
    rightPressed = false;
    breakPressed = false;
}

b2Body* CarModel::getCarBody()
{
    return body;
}

QImage CarModel::getCarImage()
{
    return image;
}

float CarModel::getCarScale()
{
    return carScale;
}

void CarModel::loadCar()
{
    // load the car sprite along with the car specific variables
    image.load(":/sprites/Resources/car2.png");
    carScale = 100;
    maxSpeed = 0.8f;
    breakSpeed = 0.04f;
    angularImpulse = 100;
    driveSpeed = 1;
    reverseSpeed = 1;
    sideVelocityMultiplyer = 0.2f;
    turnDriveRelationship = 1.5;

    b2PolygonShape driveableCarBox;
    driveableCarBox.SetAsBox(0.5f, 0.25f);
    // Define the dynamic body fixture.
    b2FixtureDef driveableCarFixtureDef;
    driveableCarFixtureDef.shape = &driveableCarBox;
    // Set the box density to be non-zero, so it will be dynamic.
    driveableCarFixtureDef.density = 10.0f;
    // Override the default friction.
    driveableCarFixtureDef.friction = 4.0f;
    if(body->GetFixtureList())
    {
        body->DestroyFixture(body->GetFixtureList());
    }
    body->CreateFixture(&driveableCarFixtureDef);
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
    turnDriveRelationship = 3.5;

    b2PolygonShape driveableCarBox;
    driveableCarBox.SetAsBox(1.f, 0.25f);
    // Define the dynamic body fixture.
    b2FixtureDef driveableCarFixtureDef;
    driveableCarFixtureDef.shape = &driveableCarBox;
    // Set the box density to be non-zero, so it will be dynamic.
    driveableCarFixtureDef.density = 4.0f;
    // Override the default friction.
    driveableCarFixtureDef.friction = 4.0f;
    if(body->GetFixtureList())
    {
        body->DestroyFixture(body->GetFixtureList());
    }
    body->CreateFixture(&driveableCarFixtureDef);
}

int CarModel::getGameLevel()
{
    return gameLevel;
}

void CarModel::setGameLevel(int currLevel)
{
    gameLevel = currLevel;
    myContactListener.setCurrLevel(currLevel);
}

void CarModel::createLevel1ParkedCars()
{
    b2BodyDef parkedCarBodyDef;
    parkedCarBodyDef.type = b2_staticBody;
    parkedCarBodyDef.position.Set(3, 1);
    b2PolygonShape otherHitboxShape;
    b2FixtureDef parkedCarFixtureDef;
    parkedCarFixtureDef.shape = &otherHitboxShape;
    parkedCarFixtureDef.density = 1.0f;
    parkedCarFixtureDef.friction = 1.0f;


    //Parked Car hitbox 1. //Good
    otherHitboxShape.SetAsBox(1.0f * 2/3, 1.0f * 0.5);
    parkedCarBodyDef.position.Set(6.5, 3.3);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar1Level1 = world.CreateBody(&parkedCarBodyDef);
    parkedCar1Level1->setHitboxType(3);
    parkedCar1Level1->setLevel(1);
    parkedCar1Level1->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 2. //Good
    otherHitboxShape.SetAsBox(1.0f * 2/3, 0.5f * 1/3);
    parkedCarBodyDef.position.Set(6.4, 5.35);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar2Level1 = world.CreateBody(&parkedCarBodyDef);
    parkedCar2Level1->setHitboxType(3);
    parkedCar2Level1->setLevel(1);
    parkedCar2Level1->CreateFixture(&parkedCarFixtureDef);
}

void CarModel::destroyLevel1ParkedCars()
{
    int numOfCarHitboxesToDelete = 2;
    while (numOfCarHitboxesToDelete > 0)
    {
       b2Body* start = world.GetBodyList();
       world.DestroyBody(start);
       numOfCarHitboxesToDelete--;
    }

}

void CarModel::createLevel2ParkedCars()
{
    b2BodyDef parkedCarBodyDef;
    parkedCarBodyDef.type = b2_staticBody;
    parkedCarBodyDef.position.Set(3, 1);
    b2PolygonShape otherHitboxShape;
    b2FixtureDef parkedCarFixtureDef;
    parkedCarFixtureDef.shape = &otherHitboxShape;
    parkedCarFixtureDef.density = 1.0f;
    parkedCarFixtureDef.friction = 1.0f;


    //Parked Car hitbox 1. //Good
    otherHitboxShape.SetAsBox(1.0f * 2/3, 1.0f * 4);
    parkedCarBodyDef.position.Set(6.5, 7.5);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar1Level2 = world.CreateBody(&parkedCarBodyDef);
    parkedCar1Level2->setHitboxType(3);
    parkedCar1Level2->setLevel(2);
    parkedCar1Level2->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 2. //Good
    otherHitboxShape.SetAsBox(1.0f * 2/3, 0.5f * 1/3);
    parkedCarBodyDef.position.Set(6.5, 0.8);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar2Level2 = world.CreateBody(&parkedCarBodyDef);
    parkedCar2Level2->setHitboxType(3);
    parkedCar2Level2->setLevel(2);
    parkedCar2Level2->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 3. //Good
    otherHitboxShape.SetAsBox(1.0f * 2/3, 0.5f * 1/3);
    parkedCarBodyDef.position.Set(6.5, 2.1);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar3Level2 = world.CreateBody(&parkedCarBodyDef);
    parkedCar3Level2->setHitboxType(3);
    parkedCar3Level2->setLevel(2);
    parkedCar3Level2->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 4. //Good
    otherHitboxShape.SetAsBox(1.0f, 1.5f);
    parkedCarBodyDef.position.Set(0, 7);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar4Level2 = world.CreateBody(&parkedCarBodyDef);
    parkedCar4Level2->setHitboxType(3);
    parkedCar4Level2->setLevel(2);
    parkedCar4Level2->CreateFixture(&parkedCarFixtureDef);
}

void CarModel::destroyLevel2ParkedCars()
{
    int numOfCarHitboxesToDelete = 4;
    while (numOfCarHitboxesToDelete > 0)
    {
       b2Body* start = world.GetBodyList();
       world.DestroyBody(start);
       numOfCarHitboxesToDelete--;
    }
}

void CarModel::createLevel3ParkedCars()
{
    b2BodyDef parkedCarBodyDef;
    parkedCarBodyDef.type = b2_staticBody;
    parkedCarBodyDef.position.Set(3, 1);
    b2PolygonShape otherHitboxShape;
    b2FixtureDef parkedCarFixtureDef;
    parkedCarFixtureDef.shape = &otherHitboxShape;
    parkedCarFixtureDef.density = 1.0f;
    parkedCarFixtureDef.friction = 1.0f;

    b2BodyDef goalBodyDef;
    goalBodyDef.type = b2_staticBody;
    goalBodyDef.position.Set(1, 1);
    b2FixtureDef goalFixtureDef;
    goalFixtureDef.shape = &otherHitboxShape;
    goalFixtureDef.isSensor = true;
    goalFixtureDef.density = 1.0f;
    goalFixtureDef.friction = 1.0f;

    b2BodyDef hazardBodyDef;
    hazardBodyDef.type = b2_staticBody;
    hazardBodyDef.position.Set(2, 1);
    b2FixtureDef hazardFixtureDef;
    hazardFixtureDef.shape = &otherHitboxShape;
    hazardFixtureDef.isSensor = true;
    hazardFixtureDef.density = 1.0f;
    hazardFixtureDef.friction = 1.0f;


    //Parked Car hitbox 1. //Good
    otherHitboxShape.SetAsBox(1.0f, 1.0f * 10);
    parkedCarBodyDef.position.Set(6.8, 0);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar1Level3 = world.CreateBody(&parkedCarBodyDef);
    parkedCar1Level3->setHitboxType(3);
    parkedCar1Level3->setLevel(3);
    parkedCar1Level3->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 2. //Good
    otherHitboxShape.SetAsBox(0.5f, 1.5f);
    parkedCarBodyDef.position.Set(0, 7);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar2Level3 = world.CreateBody(&parkedCarBodyDef);
    parkedCar2Level3->setHitboxType(3);
    parkedCar2Level3->setLevel(3);
    parkedCar2Level3->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 3. //Good
    otherHitboxShape.SetAsBox(0.5, 1.5f);
    parkedCarBodyDef.position.Set(0, 0);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar3Level3 = world.CreateBody(&parkedCarBodyDef);
    parkedCar3Level3->setHitboxType(3);
    parkedCar3Level3->setLevel(3);
    parkedCar3Level3->CreateFixture(&parkedCarFixtureDef);


    //Goal hitbox Left
    //Goal Hitbox Left Side. //Good
    otherHitboxShape.SetAsBox(1.0f * 3, 1.0f * 10);
    goalBodyDef.position.Set(0, 0);
    goalFixtureDef.shape = &otherHitboxShape;
    b2Body* leftmostGoalHitbox = world.CreateBody(&goalBodyDef);
    leftmostGoalHitbox->setHitboxType(1);
    leftmostGoalHitbox->setLevel(3);
    leftmostGoalHitbox->CreateFixture(& goalFixtureDef);


    //Hazard hitboxes
    //Hazard hitbox left 1. //Good
    otherHitboxShape.SetAsBox(1.0f, 0.1f);
    hazardBodyDef.position.Set(0, 1.9f);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* leftHazard1Hitbox = world.CreateBody(&hazardBodyDef);
    leftHazard1Hitbox->setHitboxType(2);
    leftHazard1Hitbox->setLevel(3);
    leftHazard1Hitbox->CreateFixture(&hazardFixtureDef);


    //Hazard hitbox left 2. //Good
    otherHitboxShape.SetAsBox(1.0f, 0.1f);
    hazardBodyDef.position.Set(0, 1.0f * 3.65);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* leftHazard2Hitbox = world.CreateBody(&hazardBodyDef);
    leftHazard2Hitbox->setHitboxType(2);
    leftHazard2Hitbox->setLevel(3);
    leftHazard2Hitbox->CreateFixture(&hazardFixtureDef);


    //Hazard hitbox left 3. //Good
    otherHitboxShape.SetAsBox(1.0f, 0.1f);
    hazardBodyDef.position.Set(0, 1.0f * 5.35);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* leftHazard3Hitbox = world.CreateBody(&hazardBodyDef);
    leftHazard3Hitbox->setHitboxType(2);
    leftHazard3Hitbox->setLevel(3);
    leftHazard3Hitbox->CreateFixture(&hazardFixtureDef);


    //Hazard hitbox left 4. //Good
    otherHitboxShape.SetAsBox(1.0f, 0.1f);
    hazardBodyDef.position.Set(0, 1.0f * 7.1);
    hazardFixtureDef.shape = &otherHitboxShape;
    b2Body* leftHazard4Hitbox = world.CreateBody(&hazardBodyDef);
    leftHazard4Hitbox->setHitboxType(2);
    leftHazard4Hitbox->setLevel(3);
    leftHazard4Hitbox->CreateFixture(&hazardFixtureDef);
}

void CarModel::destroyLevel3ParkedCars()
{
    int numOfCarHitboxesToDelete = 8;
    while (numOfCarHitboxesToDelete > 0)
    {
       b2Body* start = world.GetBodyList();
       world.DestroyBody(start);
       numOfCarHitboxesToDelete--;
    }
}

void CarModel::createLevel4ParkedCars()
{
    b2BodyDef parkedCarBodyDef;
    parkedCarBodyDef.type = b2_staticBody;
    parkedCarBodyDef.position.Set(3, 1);
    b2PolygonShape otherHitboxShape;
    b2FixtureDef parkedCarFixtureDef;
    parkedCarFixtureDef.shape = &otherHitboxShape;
    parkedCarFixtureDef.density = 1.0f;
    parkedCarFixtureDef.friction = 1.0f;


    //Parked Car hitbox 1. //Good
    otherHitboxShape.SetAsBox(1.0f, 1.0f * 5.5f);
    parkedCarBodyDef.position.Set(7.0f, 0);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar1Level4 = world.CreateBody(&parkedCarBodyDef);
    parkedCar1Level4->setHitboxType(3);
    parkedCar1Level4->setLevel(4);
    parkedCar1Level4->CreateFixture(&parkedCarFixtureDef);
}

void CarModel::destroyLevel4ParkedCars()
{
    int numOfCarHitboxesToDelete = 1;
    while (numOfCarHitboxesToDelete > 0)
    {
       b2Body* start = world.GetBodyList();
       world.DestroyBody(start);
       numOfCarHitboxesToDelete--;
    }
}

void CarModel::createLevel5ParkedCars()
{
    b2BodyDef parkedCarBodyDef;
    parkedCarBodyDef.type = b2_staticBody;
    parkedCarBodyDef.position.Set(3, 1);
    b2PolygonShape otherHitboxShape;
    b2FixtureDef parkedCarFixtureDef;
    parkedCarFixtureDef.shape = &otherHitboxShape;
    parkedCarFixtureDef.density = 1.0f;
    parkedCarFixtureDef.friction = 1.0f;

    b2BodyDef goalBodyDef;
    goalBodyDef.type = b2_staticBody;
    goalBodyDef.position.Set(1, 1);
    b2FixtureDef goalFixtureDef;
    goalFixtureDef.shape = &otherHitboxShape;
    goalFixtureDef.isSensor = true;
    goalFixtureDef.density = 1.0f;
    goalFixtureDef.friction = 1.0f;


    //Parked Car hitbox 1. //Good
    otherHitboxShape.SetAsBox(1.0f, 1.0f * 10);
    parkedCarBodyDef.position.Set(6.8, 0);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar1Level5 = world.CreateBody(&parkedCarBodyDef);
    parkedCar1Level5->setHitboxType(3);
    parkedCar1Level5->setLevel(5);
    parkedCar1Level5->CreateFixture(&parkedCarFixtureDef);


    //Parked Car hitbox 2. //Good
    otherHitboxShape.SetAsBox(0.20f, 1.5f);
    parkedCarBodyDef.position.Set(0, 0);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar2Level5 = world.CreateBody(&parkedCarBodyDef);
    parkedCar2Level5->setHitboxType(3);
    parkedCar2Level5->setLevel(5);
    parkedCar2Level5->CreateFixture(&parkedCarFixtureDef);



    //Parked Car hitbox 3. //Good
    otherHitboxShape.SetAsBox(0.20f, 0.75f);
    parkedCarBodyDef.position.Set(0, 3.3);
    parkedCarFixtureDef.shape = &otherHitboxShape;
    b2Body* parkedCar3Level5 = world.CreateBody(&parkedCarBodyDef);
    parkedCar3Level5->setHitboxType(3);
    parkedCar3Level5->setLevel(5);
    parkedCar3Level5->CreateFixture(&parkedCarFixtureDef);


    //Goal hitbox Left
    //Goal Hitbox Left Side. //Good
    otherHitboxShape.SetAsBox(1.0f * 3, 1.0f * 10);
    goalBodyDef.position.Set(0, 0);
    goalFixtureDef.shape = &otherHitboxShape;
    b2Body* leftmostGoalHitbox = world.CreateBody(&goalBodyDef);
    leftmostGoalHitbox->setHitboxType(1);
    leftmostGoalHitbox->setLevel(5);
    leftmostGoalHitbox->CreateFixture(& goalFixtureDef);
}

void CarModel::destroyLevel5ParkedCars()
{
    int numOfCarHitboxesToDelete = 4;
    while (numOfCarHitboxesToDelete > 0)
    {
       b2Body* start = world.GetBodyList();
       world.DestroyBody(start);
       numOfCarHitboxesToDelete--;
    }
}

void CarModel::destroyPreviousLevelHitboxes()
{
    switch (gameLevel)
    {
        case 0: break;
        case 1: destroyLevel1ParkedCars(); break;
        case 2: destroyLevel2ParkedCars(); break;
        case 3: destroyLevel3ParkedCars(); break;
        case 4: destroyLevel4ParkedCars(); break;
        case 5: destroyLevel5ParkedCars(); break;
        default: break;
    }
}
