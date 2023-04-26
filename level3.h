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
    void successfullyParked();
    void failed();
    void instructionsClicked();
    void prepareToShow();
    void checkPark();
    void hideInstructionButton();

private:
    Ui::Level3 *ui;
};

#endif // LEVEL3_H
