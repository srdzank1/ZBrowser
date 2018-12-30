#include "cverifydialog.h"

CVerifyDialog::CVerifyDialog(QWidget *parent) : QWidget(parent)
{
    userLabel = new QLabel(this);
    userEdit = new QLineEdit(this);
    passLabel = new QLabel(this);
    passEdit = new QLineEdit(this);
    okButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    userEdit->setFocus();
}

CVerifyDialog::~CVerifyDialog()
{
    delete userLabel;
    delete userEdit;
    delete passLabel;
    delete passEdit;
    delete okButton;
    delete cancelButton;
}

void CVerifyDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();
}

void CVerifyDialog::dialogSettings(){
    QFont cFont;

    l = new QLabel(this);
    l->setGeometry(20,10, 300, 30);
    cFont.setPointSize(16);
    cFont.setBold(true);
    l->setFont(cFont);
    l->setText(QStringLiteral("Registration"));


    userLabel->setGeometry(20, 50, 100, 30);
    cFont.setPointSize(10);
    cFont.setBold(false);
    userLabel->setFont(cFont);
    userLabel->setText(QStringLiteral("Enter valid email\n to get code"));

    userEdit->setGeometry(140, 50, 200, 30);
    cFont.setPointSize(10);
    userEdit->setFont(cFont);
    userEdit->setText("");

    passLabel->setGeometry(20, 85, 100, 30);
    cFont.setPointSize(10);
    cFont.setBold(false);
    passLabel->setFont(cFont);
    passLabel->setText(QStringLiteral("Code"));

    passEdit->setGeometry(140, 85, 200, 30);
    cFont.setPointSize(10);
    passEdit->setEchoMode(QLineEdit::Password);
    passEdit->setFont(cFont);
    passEdit->setText("");

    okButton->setGeometry( QRect(20 , 140, 100 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    okButton->setFont(cFont);
    okButton->setText(QStringLiteral("Ok"));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(procOk(bool)));
    okButton->show();

    cancelButton->setGeometry( QRect(120 , 140, 100 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    cancelButton->setFont(cFont);
    cancelButton->setText(QStringLiteral("Cancel"));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(procCancel(bool)));
    cancelButton->show();
}

void CVerifyDialog::procOk(bool stat){
    emit clickOK();
}

void CVerifyDialog::procCancel(bool stat){
    emit clickCancel();
}


