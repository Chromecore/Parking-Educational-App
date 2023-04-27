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

class Level2 : public QWidget
{
    Q_OBJECT

public:
    explicit Level2(QWidget *parent = nullptr);
    ~Level2();

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

private:
    Ui::Level2 *ui;
};

#endif // LEVEL2_H
