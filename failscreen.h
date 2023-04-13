#ifndef FAILSCREEN_H
#define FAILSCREEN_H

#include <QWidget>

namespace Ui {
class FailScreen;
}

class FailScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FailScreen(QWidget *parent = nullptr);
    ~FailScreen();

private:
    Ui::FailScreen *ui;
};

#endif // FAILSCREEN_H
