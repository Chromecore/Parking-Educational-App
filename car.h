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

private:
    Ui::Car *ui;
    const bool shouldDrawGizmos = false;

    // Rotates a pixmap around a pivot point based on an angle and returns the offset
    QPixmap rotatePixmap(QPixmap pixmap, QPointF pivot, qreal angle, QPointF &offset);
    // Displays gizmos relating to the car
    void drawGizmos(float x, float y, float scale);

private slots:
    // Lets the model know when the home button is clicked
    void homeButtonClicked();
    // Updated the UI
    void updateUI();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // CAR_H
