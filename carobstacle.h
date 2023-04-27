/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef CAROBSTACLE_H
#define CAROBSTACLE_H

#include <QWidget>

namespace Ui {
class CarObstacle;
}

// Widget for static car obstacles
class CarObstacle : public QWidget
{
    Q_OBJECT

public:
    QImage image;
    // Constructs a car obstacle
    explicit CarObstacle(QWidget *parent = nullptr);
    // Destructs a car obstacle
    ~CarObstacle();

private:
    Ui::CarObstacle *ui;
    std::string route;
protected:
    //paints the car obstacle
    void paintEvent(QPaintEvent *);
};

#endif // CAROBSTACLE_H
