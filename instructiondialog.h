/*
Coleman Cook, Jack Koster, Jonathan Mercado, Tayin Wallace
CS 3505
A8: Educational App
*/

#ifndef INSTRUCTIONDIALOG_H
#define INSTRUCTIONDIALOG_H

#include <QDialog>
#include <QMovie>
#include <vector>

namespace Ui {
class InstructionDialog;
}

class InstructionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InstructionDialog(QWidget *parent = nullptr, int levelNum = 0);
    ~InstructionDialog();

private:
    Ui::InstructionDialog *ui;
    QMovie* movie;
    std::vector<QString> instructions;
    int stepIndex;

    void showParallelTips();
    void showBackingTips();
    void showPerpendicularTips();

private slots:
    void showControls();
    void hideControls();
    void previousStep();
    void nextStep();

};

#endif // INSTRUCTIONDIALOG_H
