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
#include <vector>

using std::vector;

// Backing logic model class for the driving educational app
class Model : public QObject
{
    Q_OBJECT
public:
    // Constructs a model object
    explicit Model(QObject *parent = nullptr);
    Model(const Model& obj) = delete;
    // Sets the model's mainwindow
    void setMainWindow(MainWindow* mainWindowPtr);
    // Sets the model's welcome screen
    void setWelcomeScreen(WelcomeScreen* welcomeScreenPtr);

    //set up instance
    static void init();
    static Model* instance;

    // converts degrees to radians
    static float degToRad(float deg);
    // Loads dialog to the matrix
    void loadDialogToArray();

    // Dialog matrix to be used for pop up text boxes.
    vector<vector<QString>> dialog;

    static float PI;

    CarModel* carModel;
    int curLevel;
    int numLevels;
    bool canDrive;
    bool levelsCompleted[5] { 0 };

public slots:
    // Runs app to the level select screen
    void runLevelSelect();
    // Makes app go to the welcome screen
    void goHome();
    // Moves app into level1
    void runLevel1();
    // Moves app into level2
    void runLevel2();
    // Moves app into level3
    void runLevel3();
    // Moves app into level4
    void runLevel4();
    // Moves app into level5
    void runLevel5();
    // Shows success screen in app
    void successfulPark();
    // Shows failure screen in app
    void failedPark();
    // Makes app begin current level again
    void retryLevel();
    // Moves app into the next level
    void runNextLevel();
    // Creates an Instruction Dialog and runs it for the current level
    void showInstructions(QWidget *parent);

signals:
    // Signals a key being pressed
    void keyPressed(QKeyEvent* event);
    // Signals a key being released
    void keyRelease(QKeyEvent* event);
    // Signals the app going to level select screen
    void runningLevelSelect();
    // Signals the app going to welcome screen
    void goingHome();
    // Signals the app going to level1
    void level1Started();
    // Signals the app going to level2
    void level2Started();
    // Signals the app going to level3
    void level3Started();
    // Signals the app going to level4
    void level4Started();
    // Signals the app going to level5
    void level5Started();
    // Signals the user passed a level
    void showLevelComplete();
    // Signals the user completed the final level
    void showTutorialComplete(bool allLevelsComplete);
    // Signals the user failed a level
    void showLevelFailure();
};

#endif // MODEL_H
