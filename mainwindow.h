/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void hideAllWidgets();

public slots:
    void showWelcomeWidget();
    void showLevelSelectWidget();
    void showLevel1Widget();
    void showLevel2Widget();
    void showLevel3Widget();
    void showLevel4Widget();
    void showLevel5Widget();
    void showSuccessWidget();
    void showFailWidget();
    void showCertificateWidget(bool tutorialComplete);

private:
    Ui::MainWindow *ui;

protected:
    void keyPressEvent( QKeyEvent * event );
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
