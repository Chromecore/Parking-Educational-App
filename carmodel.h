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
    // How much to scale the Box2D positions into the UI positions
    const float positionScaler = 80;

    //Added for Collision Testing
    ContactListener myContactListener;
    bool isParkedSuccessfully;

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

    // Fastest speed the car can go
    float maxSpeed;
    // The speed at which the car breaks
    float breakSpeed;
    // The angular impulse used when turning
    float angularImpulse;
    // The speed that the car accelerates at when driving
    float driveSpeed;
    // The speed that the car accelerates at when reversing
    float reverseSpeed;
    // The amount of side velocity to keep (0 - none, 1 - all)
    float sideVelocityMultiplyer;
    // The relationship between the amount the car can turn vs the speed of the car
    // 0 - Can turn with 0 velocity
    // The higher the number the faster the car must be going for the car to turn
    float turnDriveRelationship;

    float carScale;
    const float drivableAreaWidth = 600;
    const float screenWidth = 800;

    // movement keys
    const Qt::Key driveKey = Qt::Key_W;
    const Qt::Key reverseKey = Qt::Key_S;
    const Qt::Key leftKey = Qt::Key_A;
    const Qt::Key rightKey = Qt::Key_D;
    const Qt::Key breakKey = Qt::Key_Return;

    // input variables
    bool drivePressed;
    bool leftPressed;
    bool reversePressed;
    bool rightPressed;
    bool breakPressed;

    //used to reference all body definitions.
    std::vector<b2BodyDef> bodyDefinitions;
    //used to reference all fixture definitions.
    std::vector<b2FixtureDef> fixtureDefinitions;

    // take in key pressed events and record them to be applied later
    void keyPressed(QKeyEvent* event);
    // take in key released events and record them to be applied later
    void keyRelease(QKeyEvent *event);
    // applies the input given from the main window to the car
    void appliesInput();
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
