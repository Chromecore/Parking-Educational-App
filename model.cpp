/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#include "model.h"
#include "car.h"

Model* Model::instance;
float Model::PI = acos(-1.0);

Model::Model(QObject *parent)
    : QObject{parent}
{

}

void Model::init(){
    instance = new Model();
}

void Model::runLevelSelect()
{
    emit runningLevelSelect();
}

void Model::goHome()
{
    emit goingHome();
}

void Model::runLevel1()
{
    emit level1Started();
}

void Model::runLevel2()
{
    emit level2Started();
}

void Model::runLevel3()
{
    emit level3Started();
}

float Model::degToRad(float degree)
{
    return PI * (180 - degree) / 180;
}

void Model::loadDialogToArray()
{

}


// Probably only needed for testButton
void Model::runCarWidget()
{
    emit runningCarWidget();
}
