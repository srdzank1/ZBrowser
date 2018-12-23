#ifndef CVerifyDialog_H
#define CVerifyDialog_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class CVerifyDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CVerifyDialog(QWidget *parent = nullptr);
    ~CVerifyDialog();
    void dialogSettings();
    QLineEdit *userEdit;
    QLineEdit *passEdit;

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void clickOK();
    void clickCancel();
public slots:
    void procOk(bool);
    void procCancel(bool);
private:
    QLabel *userLabel;
    QLabel *passLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *l;
};

#endif // CVerifyDialog_H
