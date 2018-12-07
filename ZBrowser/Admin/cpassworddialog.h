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
    QLineEdit *userEdit;
    QLabel *passLabel;
    QLineEdit *passEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // CPASSWORDDIALOG_H
