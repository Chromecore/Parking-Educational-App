/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef CARMODEL_H
#define CARMODEL_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QWidget>
#include "contactlistener.h"

class CarModel : public QObject
{
    Q_OBJECT
public:
    explicit CarModel(QObject *parent = nullptr);

    // Sets the position of the car
    void setCarPosition(b2Vec2 newPosition);
    // Sets the angle of the car in degrees
    void setCarAngle(float newAngle);
    // Sets the cars velocity to 0
    void zeroOutVelocity();
    // Returns the body used for the car physics
    b2Body* getCarBody();
    // Returns the body used for the test hitbox
    b2Body* getTestHitbox();
    // Returns the image used to display the car
    QImage getCarImage();
    // Returns the image used to display the hitboxes
    QImage getHitboxImage();
    // Returns the scale of the car
    float getCarScale();

    //To Delete
    b2Body* testHitbox;

    //Added for Collision
    enum _entityCategory {
      DRIVEABLE_CAR_HITBOX      =        0x0001,
      GOAL_HITBOX               =        0x0002,
      HAZARD_HITBOX             =        0x0004,
      PARKED_CAR_HITBOX         =        0x0008,
    };

    // How much extra to scale the car at diagonal directions
    const float scalerAt45Deg = 0.38f;
    // how much to scale the Box2D positions into the UI positions
    const float positionScaler = 80;

    // temp for collision testing
    ContactListener myContactListener;
    bool isParkedSuccessfully;

    // sets the position of the car
    void setCarPosition(b2Vec2 newPosition);
    // sets the angle of the car in degrees
    void setCarAngle(float newAngle);
    // sets the cars velocity to 0
    void zeroOutVelocity();
    // returns the body used for the car physics
    b2Body* getCarBody();
    // returns the image used to display the car
    QImage getCarImage();
    // returns the scale of the car
    float getCarScale();

signals:
    void updateUI();

private slots:
    // updates the world the car is in
    void updateWorld();


private:
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
    QImage hitBoxImage;

    // fastest speed the car can go
    float maxSpeed;
    // the speed at which the car breaks
    float breakSpeed;
    // the angular impulse used when turning
    float angularImpulse;
    // the speed that the car accelerates at when driving
    float driveSpeed;
    // the speed that the car accelerates at when reversing
    float reverseSpeed;
    // the amount of side velocity to keep (0 - none, 1 - all)
    float sideVelocityMultiplyer;
    // the relationship between the amount the car can turn vs the speed of the car
    // 0 - can turn with 0 velocity
    // the higher the number the faster the car must be going for the car to turn
    float turnDriveRelationship;

    float carScale;
    // the width of the area the car can drive in. Starts in the top left corner
    const float drivableAreaWidth = 600;
    const float screenWidth = 800;

    // movement keys
    const Qt::Key driveKey = Qt::Key_W;
    const Qt::Key reverseKey = Qt::Key_S;
    const Qt::Key leftKey = Qt::Key_A;
    const Qt::Key rightKey = Qt::Key_D;
    const Qt::Key breakKey = Qt::Key_Return;

    // keeps track of the input
    bool drivePressed;
    bool leftPressed;
    bool reversePressed;
    bool rightPressed;
    bool breakPressed;

    //used to reference all body definitions.
    std::vector<b2BodyDef> bodyDefinitions;
    //used to reference all fixture definitions.
    std::vector<b2FixtureDef> fixtureDefinitions;

    // sets up the image, collider, and other components of the car
    void setupCar();
    // sets up the colliders
    void setupColliders();
    // clamps the car speed with a max speed
    void clampCarSpeed();
    // handles the win, lose, and obsticle collisions
    void handleCollisions();
    // determins how much side velocity to keep when turning
    void handleDrifting();
    // clamps the car to stop it from driving off the screen
    void clampCarPosition();
    // take in key pressed events and record them to be applied later
    void keyPressed(QKeyEvent* event);
    // take in key released events and record them to be applied later
    void keyRelease(QKeyEvent *event);
    // applies the input given from the main window to the car
    void applyInput();
    // loads the data related to the car
    void loadCar();
    // loads the data related to the truck
    void loadTruck();
    // sets up all body definitions for hitboxes. 0 is driveable car,
    // 1 is the goal hitbox, 2 is the not intangible hitbox (think yellow lines)
    // 3 is tangible hitboxes (think parked cars)
    void createAllHitboxBodyDefinitions();

};

#endif // CARMODEL_H
