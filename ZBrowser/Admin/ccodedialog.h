#ifndef CCodeDialog_H
#define CCodeDialog_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class CCodeDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CCodeDialog(QWidget *parent = nullptr);
    ~CCodeDialog();
    void dialogSettings();
    QLineEdit *userEdit;
    QLineEdit *passEdit;
    QLineEdit *passEdit2;

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void clickOK();
    void clickCancel();
    void clickAskCode();
public slots:
    void procOk(bool);
    void procCancel(bool);
    void procAskCode(bool);
private:
    QLabel *userLabel;
    QLabel *passLabel;
    QLabel *passLabel2;

    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *AskCodeButton;
    QLabel *l;
};

#endif // CCodeDialog_H
