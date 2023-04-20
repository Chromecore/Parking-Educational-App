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
    void homeButtonClicked();

    void on_checkButton_clicked();

    void successfullyParked();

    void failed();
    void instructionsClicked();
    void prepareToShow();
private:
    Ui::Level2 *ui;
};

#endif // LEVEL2_H
