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
    loadDialogueToArray();

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
    InstructionDialog instructions(parent);
}

float Model::degToRad(float degree)
{
    return PI * (180 - degree) / 180;
}

void Model::loadDialogueToArray()
{
    //Do not change from directory. Dialogue can be added into the file, deleted, etc. so long as the file maintains its structure.
    QString filepath = ":/Dialogue/Resources/Dialogue.txt";
    QFile fileObj(filepath);
    fileObj.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = fileObj.readAll();
    fileObj.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();

    QJsonValue value = object.value("Dialogue");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue & v, array)
    {
        QString line = v.toString();
        dialogue.append(line);
    }
    /*
    foreach (const QString & s, dialogue)
        qDebug() << s;
    */
}
