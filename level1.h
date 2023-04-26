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
    // Lets the model know when the home button is clicked
    void homeButtonClicked();
    void successfullyParked();
    void failed();
    void instructionsClicked();
    void prepareToShow();
    void checkPark();
};

#endif // LEVEL1_H
