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

class CarModel : public QObject
{
    Q_OBJECT
public:
    explicit CarModel(QObject *parent = nullptr);

    void setCarPosition(b2Vec2 newPosition);
    void setCarAngle(float newAngle);
    void zeroOutVelocity();
    b2Body* getCarBody();
    QImage getCarImage();
    float getCarScale();

    // How much extra to scale the car at diagonal directions
    const float scalerAt45Deg = 0.38f;

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
    const float maxSpeed = 0.6f;
    // The speed at which the car breaks
    const float breakSpeed = 0.05f;
    // The angular impulse used when turning
    const float angularImpulse = 300;
    // The speed that the car accelerates at when driving
    const float driveSpeed = 3;
    // The speed that the car accelerates at when reversing
    const float reverseSpeed = 8;
    // The amount of side velocity to keep (0 - none, 1 - all)
    const float sideVelocityMultiplyer = 0;

    const float carScale = 100;
    const b2Vec2 startingPosition = b2Vec2(4, 4);
    const float screenWidth = 800;

protected:
    // take in key input as an event and convert it to an action performed on the car
    void keyPressed(QKeyEvent* event);
};

#endif // CARMODEL_H
