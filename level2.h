/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef LEVEL2_H
#define LEVEL2_H

#include <QWidget>

namespace Ui {
class Level2;
}

// Level widget for level two, backing parking a car
class Level2 : public QWidget
{
    Q_OBJECT

public:
    // Constructs Level2 widget
    explicit Level2(QWidget *parent = nullptr);
    // Destructs Level2 widget
    ~Level2();

private slots:
    // Lets the model know when the home button is clicked to display home screen
    void homeButtonClicked();
    // Tells model that the user parked successfully
    void successfullyParked();
    // Tells model the user failed to park
    void failed();
    // Tells model to show parking instructions
    void instructionsClicked();
    // Shows instructions button
    void prepareToShow();
    // Checks whether the user parked correctly and notifies the model
    void checkPark();
    // Hides instruction button
    void hideInstructionButton();

private:
    Ui::Level2 *ui;
};

#endif // LEVEL2_H
