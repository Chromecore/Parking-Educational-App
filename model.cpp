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

Model* Model::instance;
float Model::PI = acos(-1.0);

Model::Model(QObject *parent)
    : QObject{parent}
{

    loadDialogToArray();

    curLevel = 0;
    numLevels = 3;
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
    canDrive = false;
    emit goingHome();
}

void Model::runLevel1()
{
    canDrive = true;
    curLevel = 1;
    emit level1Started();
}

void Model::runLevel2()
{
    canDrive = true;
    curLevel = 2;
    emit level2Started();
}

void Model::runLevel3()
{
    canDrive = true;
    curLevel = 3;
    emit level3Started();
}

void Model::successfulPark()
{
    canDrive = false;
    if (curLevel == numLevels)
    {
        emit showTutorialComplete();
    }
    else
    {
        emit showLevelComplete();
    }
}

void Model::failedPark()
{
    canDrive = false;
    emit showLevelFailure();
}

float Model::degToRad(float degree)
{
    return PI * (180 - degree) / 180;
}

void Model::loadDialogToArray()
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


// Probably only needed for testButton
void Model::runCarWidget()
{
    canDrive = true;
    emit runningCarWidget();
}
