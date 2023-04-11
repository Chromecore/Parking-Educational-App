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

private slots:
    void updateWorld();

private:
    Ui::Car *ui;
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
    float PI;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressed(QKeyEvent* event);
};

#endif // CAR_H
