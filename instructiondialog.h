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

// QDialog window that pops up with instruction on how to park
class InstructionDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructs and runs the InstructionDialog
    explicit InstructionDialog(QWidget *parent = nullptr, int levelNum = 0);
    // Destructs the InstructionDialog
    ~InstructionDialog();

private:
    Ui::InstructionDialog *ui;
    QMovie* movie;
    std::vector<QString> instructions;
    int stepIndex;

    // Shows the tips for parallel parking
    void showParallelTips();
    // Shows the tips for backing parking
    void showBackingTips();
    // Shows the tips for perpendicular parking
    void showPerpendicularTips();

private slots:
    // Shows the controls widget, hides instructions
    void showControls();
    // Hides the controls widget and shows instructions
    void hideControls();
    // Shows the previous step if one exists
    void previousStep();
    // Shows the next step if one exists
    void nextStep();

};

#endif // INSTRUCTIONDIALOG_H
