/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QObject>
#include "carmodel.h"
#include "mainwindow.h"
#include "welcomescreen.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    Model(const Model& obj) = delete;
    void setMainWindow(MainWindow* mainWindowPtr);
    void setWelcomeScreen(WelcomeScreen* welcomeScreenPtr);
    void loadDialogueToArray();

    //set up instance
    static void init();
    static Model* instance;

    // converts degrees to radians
    static float degToRad(float deg);

    //Dialogue array to be used for pop up text boxes.
    QVector<QString> dialogue;

    static float PI;

    CarModel* carModel;
    int curLevel;
    int numLevels;
    bool canDrive;
    bool levelsCompleted[5] { 0 };

public slots:
    void runLevelSelect();
    void goHome();
    void runLevel1();
    void runLevel2();
    void runLevel3();
    void runLevel4();
    void runLevel5();
    void successfulPark();
    void failedPark();
    void retryLevel();
    void runNextLevel();

signals:
    void keyPressed(QKeyEvent* event);
    void keyRelease(QKeyEvent* event);
    void runningLevelSelect();
    void goingHome();
    void level1Started();
    void level2Started();
    void level3Started();
    void level4Started();
    void level5Started();
    void showLevelComplete();
    void showTutorialComplete(bool allLevelsComplete);
    void showLevelFailure();

private:
};

#endif // MODEL_H
