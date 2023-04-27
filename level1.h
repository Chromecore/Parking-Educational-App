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

class Level1 : public QWidget
{
    Q_OBJECT

public:
    explicit Level1(QWidget *parent = nullptr);
    ~Level1();

private:
    Ui::Level1 *ui;

private slots:
    // Lets the model know when the home button is clicked to display home screen
    void homeButtonClicked();
    //shows successful park overlay
    void successfullyParked();
    //shows failed parked overlay
    void failed();
    //shows instructions
    void instructionsClicked();
    //displays instructions button
    void prepareToShow();
    //shows failed of sucess screen based on whether or no parked correctly
    void checkPark();
    //hides instruction button
    void hideInstructionButton();
};

#endif // LEVEL1_H
