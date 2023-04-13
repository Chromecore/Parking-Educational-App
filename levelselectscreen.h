#ifndef LEVELSELECTSCREEN_H
#define LEVELSELECTSCREEN_H

#include <QWidget>

namespace Ui {
class LevelSelectScreen;
}

class LevelSelectScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelectScreen(QWidget *parent = nullptr);
    ~LevelSelectScreen();

public slots:
    void homeButtonClicked();

private:
    Ui::LevelSelectScreen *ui;
};

#endif // LEVELSELECTSCREEN_H
