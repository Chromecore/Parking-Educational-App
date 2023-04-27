/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef LEVELSELECTSCREEN_H
#define LEVELSELECTSCREEN_H

#include <QWidget>

namespace Ui {
class LevelSelectScreen;
}

// Widget for the level select screen to choose a level to play
class LevelSelectScreen : public QWidget
{
    Q_OBJECT

public:
    // Constructs level select screen widget
    explicit LevelSelectScreen(QWidget *parent = nullptr);
    // Destructs level select screen widget
    ~LevelSelectScreen();

private slots:
    // Notifies model to go to welcome screen
    void homeButtonClicked();
    // Notifies model to run level1
    void level1ButtonClicked();
    // Notifies model to run level2
    void level2ButtonClicked();
    // Notifies model to run level3
    void level3ButtonClicked();
    // Notifies model to run level4
    void level4ButtonClicked();
    // Notifies model to run level5
    void level5ButtonClicked();

private:
    Ui::LevelSelectScreen *ui;
};

#endif // LEVELSELECTSCREEN_H
