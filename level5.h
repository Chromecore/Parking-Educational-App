/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef LEVEL5_H
#define LEVEL5_H

#include <QWidget>

namespace Ui {
class Level5;
}

// Level widget for level five, parallel parking a truck
class Level5 : public QWidget
{
    Q_OBJECT

public:
    // Constructs Level5 widget
    explicit Level5(QWidget *parent = nullptr);
    // Destructs Level5 widget
    ~Level5();

private:
    Ui::Level5 *ui;

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

#endif // LEVEL5_H
