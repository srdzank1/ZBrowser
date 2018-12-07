#include "cpassworddialog.h"

CPasswordDialog::CPasswordDialog(QWidget *parent) : QWidget(parent)
{
    userLabel = new QLabel(this);
    userEdit = new QLineEdit(this);
    passLabel = new QLabel(this);
    passEdit = new QLineEdit(this);
    okButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    userEdit->setFocus();
}

CPasswordDialog::~CPasswordDialog()
{
    delete userLabel;
    delete userEdit;
    delete passLabel;
    delete passEdit;
    delete okButton;
    delete cancelButton;
}

void CPasswordDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();
}

void CPasswordDialog::dialogSettings(){
    QFont cFont;

    userLabel->setGeometry(20, 30, 100, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    userLabel->setFont(cFont);
    userLabel->setText(QStringLiteral("Username"));

    userEdit->setGeometry(140, 30, 200, 30);
    cFont.setPointSize(12);
    userEdit->setFont(cFont);
    userEdit->setText("");

    passLabel->setGeometry(20, 70, 100, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    passLabel->setFont(cFont);
    passLabel->setText(QStringLiteral("Password"));

    passEdit->setGeometry(140, 70, 200, 30);
    cFont.setPointSize(12);
    passEdit->setEchoMode(QLineEdit::Password);
    passEdit->setFont(cFont);
    passEdit->setText("");

    okButton->setGeometry( QRect(20 , 140, 100 ,30));
    cFont.setPointSize(12);
    cFont.setBold(true);
    okButton->setFont(cFont);
    okButton->setText(QStringLiteral("Ok"));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(procOk(bool)));
    okButton->show();

    cancelButton->setGeometry( QRect(120 , 140, 100 ,30));
    cFont.setPointSize(12);
    cFont.setBold(true);
    cancelButton->setFont(cFont);
    cancelButton->setText(QStringLiteral("Cancel"));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(procCancel(bool)));
    cancelButton->show();
}

void CPasswordDialog::procOk(bool stat){
    emit clickOK();
}

void CPasswordDialog::procCancel(bool stat){
    emit clickCancel();
}


