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

// The mainwindow where all the widgets of the app live
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructs the main window
    MainWindow(QWidget *parent = nullptr);
    // Destructs the main window
    ~MainWindow();
    // Hides all widgets that live in the main window
    void hideAllWidgets();

public slots:
    // Hides all widgets and shows welcome widget
    void showWelcomeWidget();
    // Hides all widgets and shows level select widget
    void showLevelSelectWidget();
    // Hides all widgets and shows level1 widget
    void showLevel1Widget();
    // Hides all widgets and shows level2 widget
    void showLevel2Widget();
    // Hides all widgets and shows level3 widget
    void showLevel3Widget();
    // Hides all widgets and shows level4 widget
    void showLevel4Widget();
    // Hides all widgets and shows level5 widget
    void showLevel5Widget();
    // Overlays the success screen over the current level
    void showSuccessWidget();
    // Overlays the fail screen over the current level
    void showFailWidget();
    // Hides all widgets and shows the certificate screen
    void showCertificateWidget(bool tutorialComplete);

private:
    Ui::MainWindow *ui;

protected:
    // If the car can drive right now, notifies model of key press
    void keyPressEvent( QKeyEvent * event );
    // If the car can drive right now, notifies model of key release
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
