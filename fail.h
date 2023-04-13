#ifndef FAIL_H
#define FAIL_H

#include <QWidget>

namespace Ui {
class Fail;
}

class Fail : public QWidget
{
    Q_OBJECT

public:
    explicit Fail(QWidget *parent = nullptr);
    ~Fail();

private:
    Ui::Fail *ui;
};

#endif // FAIL_H
