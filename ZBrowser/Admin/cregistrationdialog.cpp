#include "cregistrationdialog.h"

CRegistrationDialog::CRegistrationDialog(QWidget *parent) : QWidget(parent)
{
    userLabel = new QLabel(this);
    userEdit = new QLineEdit(this);

    passLabel = new QLabel(this);
    passEdit = new QLineEdit(this);
    passLabel2 = new QLabel(this);
    passEdit2 = new QLineEdit(this);


    okButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    userEdit->setFocus();
}

CRegistrationDialog::~CRegistrationDialog()
{
    delete userLabel;
    delete userEdit;
    delete passLabel;
    delete passEdit;
    delete okButton;
    delete cancelButton;
}

void CRegistrationDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();
}

void CRegistrationDialog::dialogSettings(){
    QFont cFont;

    l = new QLabel(this);
    l->setGeometry(20,10, 300, 30);
    cFont.setPointSize(16);
    cFont.setBold(true);
    l->setFont(cFont);
    l->setText(QStringLiteral("Registration Form"));

    //----------------------------------------------------

    userLabel->setGeometry(20, 50, 120, 40);
    cFont.setPointSize(10);
    cFont.setBold(false);
    userLabel->setFont(cFont);
    userLabel->setText(QStringLiteral("Enter valid email\nto get code"));

    userEdit->setGeometry(160, 50, 250, 30);
    cFont.setPointSize(10);
    userEdit->setFont(cFont);
    userEdit->setText("");

    //-----------------------------------------------------

    passLabel->setGeometry(20, 85, 120, 30);
    cFont.setPointSize(10);
    cFont.setBold(false);
    passLabel->setFont(cFont);
    passLabel->setText(QStringLiteral("Password"));

    passEdit->setGeometry(160, 85, 250, 30);
    cFont.setPointSize(10);
    passEdit->setEchoMode(QLineEdit::Password);
    passEdit->setFont(cFont);
    passEdit->setText("");

    //-----------------------------------------------------

    passLabel2->setGeometry(20, 120, 120, 30);
    cFont.setPointSize(10);
    cFont.setBold(false);
    passLabel2->setFont(cFont);
    passLabel2->setText(QStringLiteral("Repeat password"));

    passEdit2->setGeometry(160, 120, 250, 30);
    cFont.setPointSize(10);
    passEdit2->setEchoMode(QLineEdit::Password);
    passEdit2->setFont(cFont);
    passEdit2->setText("");

    //-----------------------------------------------------


    okButton->setGeometry( QRect(20 , 170, 100 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    okButton->setFont(cFont);
    okButton->setText(QStringLiteral("Ok"));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(procOk(bool)));
    okButton->show();

    cancelButton->setGeometry( QRect(120 , 170, 100 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    cancelButton->setFont(cFont);
    cancelButton->setText(QStringLiteral("Cancel"));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(procCancel(bool)));
    cancelButton->show();
}

void CRegistrationDialog::procOk(bool stat){
    emit clickOK();
}

void CRegistrationDialog::procCancel(bool stat){
    emit clickCancel();
}


