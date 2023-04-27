/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

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

private slots:
    //displays home screen
    void homeButtonClicked();
    //restarts level
    void retryClicked();
    //starts next level
    void nextLevelClicked();

private:
    Ui::SuccessScreen *ui;
};

#endif // SUCCESSSCREEN_H
