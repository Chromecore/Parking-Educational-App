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

class Level4 : public QWidget
{
    Q_OBJECT

public:
    explicit Level4(QWidget *parent = nullptr);
    ~Level4();

private:
    Ui::Level4 *ui;

private slots:
    // Lets the model know when the home button is clicked
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

#endif // LEVEL4_H
