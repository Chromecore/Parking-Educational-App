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

    //set up instance
    static void init();
    static Model* instance;

public slots:
    void startTutorial();
    void runLevelSelect();

signals:
    void keyPressed(QKeyEvent* event);
    void tutorialStarted();
    void runningLevelSelect();

private:
};

#endif // MODEL_H
