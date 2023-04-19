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
    void homeButtonClicked();

private:
    Ui::CertificateScreen *ui;
};

#endif // CERTIFICATESCREEN_H
