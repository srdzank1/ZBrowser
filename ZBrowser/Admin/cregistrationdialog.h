#ifndef CRegistrationDialog_H
#define CRegistrationDialog_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class CRegistrationDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CRegistrationDialog(QWidget *parent = nullptr);
    ~CRegistrationDialog();
    void dialogSettings();
    QLineEdit *userEdit;
    QLineEdit *passEdit;
    QLineEdit *passEdit2;

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
    QLabel *passLabel2;

    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *l;
};

#endif // CRegistrationDialog_H
