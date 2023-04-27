#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>

namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = nullptr);
    ~WelcomeScreen();

private slots:
    void onStartButtonClicked();
    void onLevelSelectClicked();

private:
    Ui::WelcomeScreen *ui;
    QMovie* movie;
};

#endif // WELCOMESCREEN_H
