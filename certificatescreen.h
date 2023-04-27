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

// Widget that appears with the certificate saying you learned how to park
class CertificateScreen : public QWidget
{
    Q_OBJECT

public:
    // Constructs a certificate screen widget
    explicit CertificateScreen(QWidget *parent = nullptr);
    // Destructs a certificate screen widget
    ~CertificateScreen();

private slots:
    // Notifies model to go to welcome screen
    void homeButtonClicked();
    // If all levels are complete shows final certifcate
    void showTutorialComplete(bool allLevelsComplete);

private:
    Ui::CertificateScreen *ui;
};

#endif // CERTIFICATESCREEN_H
