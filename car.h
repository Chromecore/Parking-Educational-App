/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef CAR_H
#define CAR_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

namespace Ui {
class Car;
}
class Car : public QWidget
{
    Q_OBJECT

public:
    explicit Car(QWidget *parent = nullptr);
    ~Car();
    void setCarPosition(b2Vec2 newPosition);

private slots:
    // updates the world the car is in
    void updateWorld();
    void homeButtonClicked();

private:
    Ui::Car *ui;
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
    // How much extra to scale the car at diagonal directions
    const float scalerAt45Deg = 0.38f;

    const float carScale = 100;
    const b2Vec2 startingPosition = b2Vec2(4, 4);

protected:
    void paintEvent(QPaintEvent *);
    // take in key input as an event and convert it to an action performed on the car
    void keyPressed(QKeyEvent* event);
};

#endif // CAR_H
