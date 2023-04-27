/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef CERTIFICATESCREEN_H
#define CERTIFICATESCREEN_H

#include <QWidget>

namespace Ui {
class CertificateScreen;
}

class CertificateScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CertificateScreen(QWidget *parent = nullptr);
    ~CertificateScreen();

private slots:
    //displays homescreen
    void homeButtonClicked();
    //if all levels are complete shows final certifcate
    void showTutorialComplete(bool allLevelsComplete);

private:
    Ui::CertificateScreen *ui;
};

#endif // CERTIFICATESCREEN_H
