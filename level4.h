#ifndef LEVEL4_H
#define LEVEL4_H

#include <QWidget>

namespace Ui {
class Level4;
}

class Level4 : public QWidget
{
    Q_OBJECT

public:
    explicit Level4(QWidget *parent = nullptr);
    ~Level4();

private:
    Ui::Level4 *ui;
};

#endif // LEVEL4_H
