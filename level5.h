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
    void successfullyParked();
    void failed();
    void instructionsClicked();
    void prepareToShow();
    void checkPark();
    void hideInstructionButton();
};

#endif // LEVEL5_H
