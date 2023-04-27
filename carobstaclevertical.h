/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef CAROBSTACLEVERTICAL_H
#define CAROBSTACLEVERTICAL_H

#include <QWidget>

namespace Ui {
class CarObstacleVertical;
}

class CarObstacleVertical : public QWidget
{
    Q_OBJECT

public:
    explicit CarObstacleVertical(QWidget *parent = nullptr);
    ~CarObstacleVertical();

private:
    Ui::CarObstacleVertical *ui;
    std::string route;
    int ran;
protected:
    //paints car
    void paintEvent(QPaintEvent *);
};

#endif // CAROBSTACLEVERTICAL_H
