#include "cverifydialog.h"

CRegistrationVerifyDialog::CRegistrationVerifyDialog(QWidget *parent) : QWidget(parent)
{
    emailLabel = new QLabel(this);
    userEdit = new QLineEdit(this);
    codeLabel = new QLabel(this);
    okButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    sendNewEmailButton = new QPushButton(this);
    sendNewCodeButton = new QPushButton(this);
    userEdit->setFocus();
}

CRegistrationVerifyDialog::~CRegistrationVerifyDialog()
{
    delete emailLabel;
    delete userEdit;
    delete codeLabel;
//    delete passEdit;
    delete okButton;
    delete cancelButton;
    delete sendNewEmailButton;
    delete sendNewCodeButton;

}

void CRegistrationVerifyDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();
}



void CRegistrationVerifyDialog::dialogSettings(){
    QFont cFont;

    l = new QLabel(this);
    l->setGeometry(20,10, 300, 30);
    cFont.setPointSize(16);
    cFont.setBold(true);
    l->setFont(cFont);
    l->setText(QStringLiteral("Registration"));

    // ----------------------------------------------------------

    emailLabel->setGeometry(20, 50, 350, 40);
    cFont.setPointSize(10);
    cFont.setBold(false);
    emailLabel->setFont(cFont);
    emailLabel->setText(QStringLiteral("Please retrieve the code sent by email to \n") + mEmail);

    codeLabel->setGeometry(20, 95, 350, 30);
    cFont.setPointSize(10);
    cFont.setBold(false);
    codeLabel->setFont(cFont);
    codeLabel->setText(QStringLiteral("Code "));

    userEdit->setGeometry(100, 95, 200, 30);
    cFont.setPointSize(10);
    userEdit->setFont(cFont);
    userEdit->setEchoMode(QLineEdit::Password);
    userEdit->setText("");


// ----------------------------------------------------------

    okButton->setGeometry( QRect(20 , 145, 50 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    okButton->setFont(cFont);
    okButton->setText(QStringLiteral("Ok"));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(procOk(bool)));
    okButton->show();

    cancelButton->setGeometry( QRect(70 , 145, 65 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    cancelButton->setFont(cFont);
    cancelButton->setText(QStringLiteral("Cancel"));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(procCancel(bool)));
    cancelButton->show();


    sendNewCodeButton->setGeometry( QRect(135 , 145, 115 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    sendNewCodeButton->setFont(cFont);
    sendNewCodeButton->setText(QStringLiteral("New code"));
    connect(sendNewCodeButton, SIGNAL(clicked(bool)), this, SLOT(procNewCode(bool)));
    sendNewCodeButton->show();

    sendNewEmailButton->setGeometry( QRect(250 , 145, 130 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    sendNewEmailButton->setFont(cFont);
    sendNewEmailButton->setText(QStringLiteral("Change email"));
    connect(sendNewEmailButton, SIGNAL(clicked(bool)), this, SLOT(procNewEmail(bool)));
    sendNewEmailButton->show();
}




void CRegistrationVerifyDialog::procOk(bool stat){
    emit clickOK();
}

void CRegistrationVerifyDialog::procCancel(bool stat){
    emit clickCancel();
}

void CRegistrationVerifyDialog::procNewCode(bool stat){
    emit clickNewCode();
}

void CRegistrationVerifyDialog::procNewEmail(bool stat){
    emit clickNewEmail();
}

void CRegistrationVerifyDialog::setEmailText(QString& text){
   mEmail = text;
}


