/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "model.h"

Model* Model::instance;

Model::Model(QObject *parent)
    : QObject{parent}
{

}

void Model::init(){
    instance = new Model();
}

void Model::startTutorial()
{
    emit tutorialStarted();
}

void Model::runLevelSelect()
{
    emit runningLevelSelect();
}

float Model::degToRad(float degree)
{
    float PI = acos(-1.0);
    return PI * (180 - degree) / 180;
}

void Model::loadDialogueToArray()
{

}

void Model::runCarWidget()
{
    emit runningCarWidget();
}
