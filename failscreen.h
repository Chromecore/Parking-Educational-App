/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

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

private slots:
    //displays home screen
    void homeButtonClicked();
    //restarts level
    void retryClicked();

private:
    Ui::FailScreen *ui;
};

#endif // FAILSCREEN_H
