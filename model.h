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
    void loadDialogToArray();

    //set up instance
    static void init();
    static Model* instance;

    // converts degrees to radians
    static float degToRad(float deg);

    //Dialogue array to be used for pop up text boxes.
    QVector<QString> dialogue;

    static float PI;

public slots:
    void runLevelSelect();
    void runCarWidget();
    void goHome();
    void runLevel1();
    void runLevel2();
    void runLevel3();

signals:
    void keyPressed(QKeyEvent* event);
    void runningLevelSelect();
    void runningCarWidget();
    void goingHome();
    void level1Started();
    void level2Started();
    void level3Started();

private:
};

#endif // MODEL_H
