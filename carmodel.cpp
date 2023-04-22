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

    loadCar();

    // setup the image
    float size = screenWidth / sqrt(2);
    image = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    hitBoxImage = image.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //Create all body definitions
    createAllHitboxBodyDefinitions();

    //assign car's body.
    body = world.CreateBody(&bodyDefinitions[0]);

    setCarAngle(0);



    // start the main update loop
    connect(&timer, &QTimer::timeout, this, &CarModel::updateWorld);
    timer.start(10);

    // set up Collision Testing
    body->SetUserData( body );
    world.SetContactListener(&myContactListener);
    isParkedSuccessfully = false;

    //Creation of all the hitboxes hitboxes.
    testHitbox = world.CreateBody(&bodyDefHazard);
    testHitbox->setHitboxType(2);
    testHitbox->CreateFixture(&fixtureDefHitbox);
    //b2Body* testHitBoxHazard = world.CreateBody(&bodyDefHazard);
    //testHitBoxHazard->setHitboxType(2);
    //testHitBoxHazard->CreateFixture(&fixtureDefHitbox);
}

void CarModel::updateWorld() {
    // update the world
    world.Step(1.0/60.0, 6, 2);
    emit updateUI();

    // win condition
    if (body->getHazardContactNum() > 0 ){
        qDebug() << "LOSE";
        isParkedSuccessfully = false;
    }
    else if (body->getGoalContactNum() > 0){
        qDebug() << "WIN";
        isParkedSuccessfully = true;
    }

    // check if collided with obstacle that causes automatic fail
    if (body->getFailedPark())
        Model::instance->failedPark();

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

    appliesInput();

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

void CarModel::appliesInput()
{
    // find the direction the car is facing
    float angleRad = Model::degToRad(-body->GetAngle() + 180);
    b2Vec2 direction(cos(angleRad), sin(angleRad));

    // stop from turning when not moving
    float angleEffector = 0;
    float carSpeed = sqrt(pow(body->GetLinearVelocity().x, 2) + pow(body->GetLinearVelocity().y, 2));
    angleEffector = carSpeed / turnDriveRelationship;

    b2Vec2 velocity = body->GetLinearVelocity();

//    QVector2D velVec(velocity.x, velocity.y);
//    QVector2D dirVec(direction.x, direction.y);
//    float invertTurn = velVec.dotProduct(velVec, dirVec);
//    invertTurn = invertTurn / abs(invertTurn);
//    qDebug();

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

void CarModel::createAllHitboxBodyDefinitions()
{
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

        // Define another box shape for our dynamic body.
        b2PolygonShape hitboxShape;
        hitboxShape.SetAsBox(1.0f, 1.0f/5 * 3);

    // Define the dynamic body fixture.
    b2FixtureDef driveableCarFixtureDef;
    driveableCarFixtureDef.shape = &driveableCarBox;

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDefHitbox;
        fixtureDefHitbox.shape = &hitboxShape;
        fixtureDefHitbox.isSensor = true;
       // fixtureDefHitbox.filter.categoryBits = HAZARD_HITBOX;
        //fixtureDefHitbox.filter.maskBits = DRIVEABLE_CAR_HITBOX;


    // Set the box density to be non-zero, so it will be dynamic.
    driveableCarFixtureDef.density = 1.0f;

        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDefHitbox.density = 1.0f;

    // Override the default friction.
    driveableCarFixtureDef.friction = 1.0f;
    // Add the shape to the body.
    body->CreateFixture(&driveableCarFixtureDef);

        // Override the default friction.
        fixtureDefHitbox.friction = 1.0f;
}
