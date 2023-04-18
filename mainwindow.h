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
    void showCarWidget();
    void showWelcomeWidget();
    void showLevelSelectWidget();
    void showLevel1Widget();
    void showLevel2Widget();
    void showLevel3Widget();
    void showSuccessWidget();
    void showFailWidget();

private:
    Ui::MainWindow *ui;

protected:
    void keyPressEvent( QKeyEvent * event );
};
#endif // MAINWINDOW_H
