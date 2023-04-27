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

// View class for the car
class Car : public QWidget
{
    Q_OBJECT

public:
    // Constructs car widget
    explicit Car(QWidget *parent = nullptr);
    // Destructs car widget
    ~Car();

private:
    Ui::Car *ui;
    const bool shouldDrawGizmos = false;

    // rotates a pixmap around a pivot point based on an angle and returns the offset
    QPixmap rotatePixmap(QPixmap pixmap, QPointF pivot, qreal angle, QPointF &offset);
    // displays gizmos relating to the car
    void drawGizmos(float x, float y, float scale);

private slots:
    // send a signal to update the UI
    void updateUI();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // CAR_H
