#ifndef CMessageDialog_H
#define CMessageDialog_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class CMessageDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CMessageDialog(QWidget *parent = nullptr);
    ~CMessageDialog();
    void dialogSettings(const QString&, const QString&);
    QLineEdit *userEdit;
    QLineEdit *passEdit;
    QLineEdit *passEdit2;

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:
    void clickOK();

public slots:
    void procOk(bool);

private:
    QLabel *MsgLabel;
    QPushButton *okButton;
    QLabel *l;
};

#endif // CMessageDialog_H
