/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QObject>
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

public slots:
    void startTutorial();
    void runLevelSelect();
    void runCarWidget();
    void goHome();

signals:
    void keyPressed(QKeyEvent* event);
    void tutorialStarted();
    void runningLevelSelect();
    void runningCarWidget();
    void goingHome();

private:
};

#endif // MODEL_H
