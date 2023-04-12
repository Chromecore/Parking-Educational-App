#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>

namespace Ui {
class Level1;
}

class Level1 : public QWidget
{
    Q_OBJECT

public:
    explicit Level1(QWidget *parent = nullptr);
    ~Level1();

private:
    Ui::Level1 *ui;
};

#endif // LEVEL1_H
