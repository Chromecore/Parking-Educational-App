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
    void paintEvent(QPaintEvent *);
};

#endif // CAROBSTACLEVERTICAL_H
