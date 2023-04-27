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

class Level3 : public QWidget
{
    Q_OBJECT

public:
    explicit Level3(QWidget *parent = nullptr);
    ~Level3();

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
    Ui::Level3 *ui;
};

#endif // LEVEL3_H
