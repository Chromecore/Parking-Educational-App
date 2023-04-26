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
    void successfullyParked();
    void failed();
    void instructionsClicked();
    void prepareToShow();
    void checkPark();
};

#endif // LEVEL4_H
