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

class Level5 : public QWidget
{
    Q_OBJECT

public:
    explicit Level5(QWidget *parent = nullptr);
    ~Level5();

private:
    Ui::Level5 *ui;

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

#endif // LEVEL5_H
