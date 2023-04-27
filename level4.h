/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef LEVEL4_H
#define LEVEL4_H

#include <QWidget>

namespace Ui {
class Level4;
}

// Level widget for level four, perpendicular parking a truck
class Level4 : public QWidget
{
    Q_OBJECT

public:
    explicit Level4(QWidget *parent = nullptr);
    ~Level4();

private:
    Ui::Level4 *ui;

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
};

#endif // LEVEL4_H
