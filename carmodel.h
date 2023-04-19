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
    // Returns the image used to display the car
    QImage getCarImage();
    // Returns the scale of the car
    float getCarScale();

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

    // Fastest speed the car can go
    const float maxSpeed = 0.8f;
    // The speed at which the car breaks
    const float breakSpeed = 0.04f;
    // The angular impulse used when turning
    const float angularImpulse = 300;
    // The speed that the car accelerates at when driving
    const float driveSpeed = 1;
    // The speed that the car accelerates at when reversing
    const float reverseSpeed = 1;
    // The amount of side velocity to keep (0 - none, 1 - all)
    const float sideVelocityMultiplyer = 0.2;
    // The relationship between the amount the car can turn vs the speed of the car
    // 0 - Can turn with 0 velocity
    // The higher the number the faster the car must be going for the car to turn
    const float turnDriveRelationship = 2;

    const float carScale = 100;
    const float drivableAreaWidth = 600;
    const float screenWidth = 800;

    // keys
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

    // take in key input as an event and convert it to an action performed on the car
    void keyPressed(QKeyEvent* event);
    void keyRelease(QKeyEvent *event);
    void handleInput();
};

#endif // CARMODEL_H