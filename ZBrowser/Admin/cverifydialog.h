#ifndef CVerifyDialog_H
#define CVerifyDialog_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class CRegistrationVerifyDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CRegistrationVerifyDialog(QWidget *parent = nullptr);
    ~CRegistrationVerifyDialog();
    void dialogSettings();
    void setEmailText(QString& text);

    QLineEdit *userEdit;
    QLineEdit *passEdit;

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void clickOK();
    void clickCancel();
    void clickNewCode();
    void clickNewEmail();

public slots:
    void procOk(bool);
    void procCancel(bool);
    void procNewCode(bool);
    void procNewEmail(bool);
private:
    QLabel *emailLabel;
    QLabel *codeLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *l;
    QPushButton *sendNewEmailButton;
    QPushButton *sendNewCodeButton;
    QString mEmail;
};

#endif // CVerifyDialog_H
