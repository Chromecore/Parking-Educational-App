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

// Widget that shows you failed the level
class FailScreen : public QWidget
{
    Q_OBJECT

public:
    // Constructs fail screen widget
    explicit FailScreen(QWidget *parent = nullptr);
    // Destructs fail screen widget
    ~FailScreen();

private slots:
    // Notifies model to go to welcome screen
    void homeButtonClicked();
    // Notifies model to restart level
    void retryClicked();

private:
    Ui::FailScreen *ui;
};

#endif // FAILSCREEN_H
