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

class CarObstacle : public QWidget
{
    Q_OBJECT

public:
    QImage image;
    explicit CarObstacle(QWidget *parent = nullptr);
    ~CarObstacle();

private:
    Ui::CarObstacle *ui;
    std::string route;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CAROBSTACLE_H
