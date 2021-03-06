#ifndef CPASSWORDDIALOG_H
#define CPASSWORDDIALOG_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class CPasswordDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CPasswordDialog(QWidget *parent = nullptr);
    ~CPasswordDialog();
    void dialogSettings();
    QLineEdit *userEdit;
    QLineEdit *passEdit;

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void clickOK();
    void clickCancel();
    void clickRecovery();
public slots:
    void procOk(bool);
    void procCancel(bool);
    void procRecovery(bool);
private:
    QLabel *userLabel;
    QLabel *passLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *passRecoveryButton;
    QLabel *l;
};

#endif // CPASSWORDDIALOG_H
