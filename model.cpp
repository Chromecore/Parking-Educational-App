/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "model.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include "instructiondialog.h"

Model* Model::instance;
float Model::PI = acos(-1.0);

Model::Model(QObject *parent)
    : QObject{parent}
{
    loadDialogToArray();

    curLevel = 0;
    numLevels = 5;
}

void Model::init()
{
    instance = new Model;
    instance->carModel = new CarModel;
}

void Model::runLevelSelect()
{
    canDrive = false;
    emit runningLevelSelect();
}

void Model::goHome()
{
    for (int i = 0; i < numLevels; i++)
    {
        levelsCompleted[i] = false;
    }
    canDrive = false;
    emit goingHome();
}

void Model::runLevel1()
{
    carModel->loadCar();
    carModel->setCarPosition(b2Vec2(4, 4));
    carModel->setCarAngle(0);
    carModel->zeroOutVelocity();
    carModel->getCarBody()->setFailedPark(false);
    carModel->destroyPreviousLevelHitboxes();
    carModel->setGameLevel(1);
    canDrive = true;
    curLevel = 1;
    carModel->createLevel1ParkedCars();
    emit level1Started();
}

void Model::runLevel2()
{
    carModel->loadCar();
    carModel->setCarPosition(b2Vec2(4, 4));
    carModel->setCarAngle(0);
    carModel->zeroOutVelocity();
    carModel->getCarBody()->setFailedPark(false);
    carModel->destroyPreviousLevelHitboxes();
    carModel->setGameLevel(2);
    canDrive = true;
    curLevel = 2;
    carModel->createLevel2ParkedCars();
    emit level2Started();
}

void Model::runLevel3()
{
    carModel->loadCar();
    carModel->setCarPosition(b2Vec2(4, 4));
    carModel->setCarAngle(0);
    carModel->zeroOutVelocity();
    carModel->getCarBody()->setFailedPark(false);
    carModel->destroyPreviousLevelHitboxes();
    carModel->setGameLevel(3);
    canDrive = true;
    curLevel = 3;
    carModel->createLevel3ParkedCars();
    emit level3Started();
}

void Model::runLevel4()
{
    carModel->loadTruck();
    carModel->setCarPosition(b2Vec2(4, 4));
    carModel->setCarAngle(0);
    carModel->zeroOutVelocity();
    carModel->getCarBody()->setFailedPark(false);
    carModel->destroyPreviousLevelHitboxes();
    carModel->setGameLevel(4);
    canDrive = true;
    curLevel = 4;
    carModel->createLevel4ParkedCars();
    emit level4Started();
}

void Model::runLevel5()
{
    carModel->loadTruck();
    carModel->setCarPosition(b2Vec2(4, 4));
    carModel->setCarAngle(0);
    carModel->zeroOutVelocity();
    carModel->getCarBody()->setFailedPark(false);
    carModel->destroyPreviousLevelHitboxes();
    carModel->setGameLevel(5);
    canDrive = true;
    curLevel = 5;
    carModel->createLevel5ParkedCars();
    emit level5Started();
}

void Model::successfulPark()
{
    canDrive = false;
    Model::instance->carModel->zeroOutVelocity();

    if (curLevel == numLevels)
    {
        levelsCompleted[curLevel - 1] = true;
        for (int i = 0; i < numLevels; i++)
        {
            if (!levelsCompleted[i])
            {
                emit showTutorialComplete(false);
                return;
            }
        }

        emit showTutorialComplete(true);
    }
    else
    {
        levelsCompleted[curLevel - 1] = true;
        emit showLevelComplete();
    }
}

void Model::failedPark()
{
    canDrive = false;
    Model::instance->carModel->zeroOutVelocity();
    emit showLevelFailure();
}

void Model::retryLevel()
{
    switch(curLevel)
    {
        case 1:
            runLevel1();
            break;
        case 2:
            runLevel2();
            break;
        case 3:
            runLevel3();
            break;
        case 4:
            runLevel4();
            break;
        case 5:
            runLevel5();
            break;
        default:
            break;
    }
}

void Model::runNextLevel()
{
    switch(curLevel)
    {
    case 1:
        runLevel2();
        break;
    case 2:
        runLevel3();
        break;
    case 3:
        runLevel4();
        break;
    case 4:
        runLevel5();
        break;
    default:
        break;
    }
}

void Model::showInstructions(QWidget *parent)
{
    InstructionDialog instructions(parent, curLevel);
}

float Model::degToRad(float degree)
{
    return PI * (180 - degree) / 180;
}

void Model::loadDialogToArray()
{
    vector<QString> perpendicularSteps;
    perpendicularSteps.push_back("Step 1: Signal intention and position the vehicle 5-6\nfeet away from the space.");
    perpendicularSteps.push_back("Step 2: Move forward until the side view mirror is\naligned with the first pavement line.");
    perpendicularSteps.push_back("Step 3: While driving slowly, turn the wheel sharply\nto align the vehicle parallel within the lines.");
    perpendicularSteps.push_back("Step 4: Steer towards the target in center of space\nand straighten the wheels.");
    perpendicularSteps.push_back("Step 5: Position the front bumper 3-6 inches from the\ncurb or end of the space.");
    dialog.push_back(perpendicularSteps);

    vector<QString> backingSteps;
    backingSteps.push_back("Step 1: Drive forward past the intended space while\nturning the wheel away from it.");
    backingSteps.push_back("Step 2: With the space at an angle behind your\nvehicle, begin to reverse straight toward it.");
    backingSteps.push_back("Step 3: When the back of the vehicle has started to\nenter the space, turn the wheel to align the front of\nthe vehicle in the lines.");
    backingSteps.push_back("Step 4: Use both side view mirrors to ensure the\nsides of the vehicle are within the lines.");
    backingSteps.push_back("Step 5: Carefully reverse the vehicle straight back\ninto the space and stop when the back bumper is\nabout 6 inches from the curb.");
    dialog.push_back(backingSteps);

    vector<QString> parallelSteps;
    parallelSteps.push_back("Step 1: Signal intention and drive forward past the\nintended space and stop parallel to the vehicle in\nfront about 2 feet away.");
    parallelSteps.push_back("Step 2: Stop when the back of your vehicle is aligned\nwith the back of the vehicle in front.");
    parallelSteps.push_back("Step 3: Start reversing and steer the front of your\nvehicle away from the vehicle in front until your\nvehicle is at a 35-40 degree angle.");
    parallelSteps.push_back("Step 4: Stop and straighten the wheels when your\nside view mirror is in line with the rear bumper of the\nvehicle in front of the space.");
    parallelSteps.push_back("Step 5: Continue backing slowly and turning the\nwheels in the opposite direction to swing the front of\nthe vehicle toward the curb.");
    parallelSteps.push_back("Step 6: Stop when your vehicle when it is parallel\nto the curb and center it within the space. It should\nbe 6-18 inches from the curb.");
    dialog.push_back(parallelSteps);
}
