#ifndef INSTRUCTIONDIALOG_H
#define INSTRUCTIONDIALOG_H

#include <QDialog>
#include <QMovie>

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

    void showParallelParkGif();
    void showBackingParkGif();
    void showPerpendicularParkGif();
};

#endif // INSTRUCTIONDIALOG_H
