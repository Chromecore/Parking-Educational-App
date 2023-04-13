#ifndef SUCCESSSCREEN_H
#define SUCCESSSCREEN_H

#include <QWidget>

namespace Ui {
class SuccessScreen;
}

class SuccessScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SuccessScreen(QWidget *parent = nullptr);
    ~SuccessScreen();

private:
    Ui::SuccessScreen *ui;
};

#endif // SUCCESSSCREEN_H
