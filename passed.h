#ifndef PASSED_H
#define PASSED_H

#include <QWidget>

namespace Ui {
class Passed;
}

class Passed : public QWidget
{
    Q_OBJECT

public:
    explicit Passed(QWidget *parent = nullptr);
    ~Passed();

private:
    Ui::Passed *ui;
};

#endif // PASSED_H
