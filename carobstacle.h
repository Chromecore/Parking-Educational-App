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
};

#endif // CAROBSTACLE_H
