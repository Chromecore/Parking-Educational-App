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

// Widget showing the user passed a level
class SuccessScreen : public QWidget
{
    Q_OBJECT

public:
    // Constructs success screen widget
    explicit SuccessScreen(QWidget *parent = nullptr);
    // Destructs success screen widget
    ~SuccessScreen();

private slots:
    // Notifies model to go to welcomes screen
    void homeButtonClicked();
    // Notifies model to restart the level
    void retryClicked();
    // Notifies model to move to next level
    void nextLevelClicked();

private:
    Ui::SuccessScreen *ui;
};

#endif // SUCCESSSCREEN_H
