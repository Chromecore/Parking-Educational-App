/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef LEVEL3_H
#define LEVEL3_H

#include <QWidget>

namespace Ui {
class Level3;
}

// Level widget for level three, parallel parking a car
class Level3 : public QWidget
{
    Q_OBJECT

public:
    explicit Level3(QWidget *parent = nullptr);
    ~Level3();

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
    Ui::Level3 *ui;
};

#endif // LEVEL3_H
