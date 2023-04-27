/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>

namespace Ui {
class Level1;
}

// Level widget for level one, perpendicular parking car
class Level1 : public QWidget
{
    Q_OBJECT

public:
    // Constructs Level1 widget
    explicit Level1(QWidget *parent = nullptr);
    // Destructs Level1 widget
    ~Level1();

private:
    Ui::Level1 *ui;

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

#endif // LEVEL1_H
