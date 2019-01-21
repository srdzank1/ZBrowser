﻿#include "cpassworddialog.h"

CPasswordDialog::CPasswordDialog(QWidget *parent) : QWidget(parent)
{
    userLabel = new QLabel(this);
    userEdit = new QLineEdit(this);
    okButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    passRecoveryButton = new QPushButton(this);
    userEdit->setFocus();
}

CPasswordDialog::~CPasswordDialog()
{
    delete userLabel;
    delete userEdit;
    delete okButton;
    delete cancelButton;
    delete passRecoveryButton;
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

    l = new QLabel(this);
    l->setGeometry(20,10, 300, 30);
    cFont.setPointSize(16);
    cFont.setBold(true);
    l->setFont(cFont);
    l->setText(QStringLiteral("Login"));


    userLabel->setGeometry(20, 50, 100, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    userLabel->setFont(cFont);
    userLabel->setText(QStringLiteral("Code"));

    userEdit->setGeometry(140, 50, 200, 30);
    cFont.setPointSize(12);
    userEdit->setFont(cFont);
    userEdit->setEchoMode(QLineEdit::Password);
    userEdit->setText("");

    okButton->setGeometry( QRect(20 , 140, 100 ,30));
    cFont.setPointSize(12);
    cFont.setBold(true);
    okButton->setFont(cFont);
    okButton->setText(QStringLiteral("Ok"));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(procOk(bool)));
    okButton->show();

    cancelButton->setGeometry( QRect(100 , 140, 80 ,30));
    cFont.setPointSize(12);
    cFont.setBold(true);
    cancelButton->setFont(cFont);
    cancelButton->setText(QStringLiteral("Cancel"));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(procCancel(bool)));
    cancelButton->show();

    passRecoveryButton->setGeometry( QRect(180 , 140, 200 ,30));
    cFont.setPointSize(12);
    cFont.setBold(true);
    passRecoveryButton->setFont(cFont);
    passRecoveryButton->setText(QStringLiteral("Forget Code"));
    connect(passRecoveryButton, SIGNAL(clicked(bool)), this, SLOT(procRecovery(bool)));
    passRecoveryButton->show();

}

void CPasswordDialog::procOk(bool stat){
    emit clickOK();
}

void CPasswordDialog::procCancel(bool stat){
    emit clickCancel();
}

void CPasswordDialog::procRecovery(bool stat){
    emit clickRecovery();
}

