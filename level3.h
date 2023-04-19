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
    void on_homeButton_clicked();

    void on_checkButton_clicked();

    void successfullyParked();

    void failed();
private:
    Ui::Level3 *ui;
};

#endif // LEVEL3_H
