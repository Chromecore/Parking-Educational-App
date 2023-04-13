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
