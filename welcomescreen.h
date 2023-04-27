/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>

namespace Ui {
class WelcomeScreen;
}

// Home screen widget for the app
class WelcomeScreen : public QWidget
{
    Q_OBJECT

public:
    // Constructs the welcome screen widget
    explicit WelcomeScreen(QWidget *parent = nullptr);
    // Destructs teh welcome screen widget
    ~WelcomeScreen();

private slots:
    // Notifies the model to start the tutorial
    void onStartButtonClicked();
    // Notifies the model to show level select screen
    void onLevelSelectClicked();

private:
    Ui::WelcomeScreen *ui;
    QMovie* movie;
};

#endif // WELCOMESCREEN_H
