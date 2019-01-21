#include "cregistrationdialog.h"

CRegistrationDialog::CRegistrationDialog(QWidget *parent) : QWidget(parent)
{
    userLabel = new QLabel(this);
    userEdit = new QLineEdit(this);

    okButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    userEdit->setFocus();
}

CRegistrationDialog::~CRegistrationDialog()
{
    delete userLabel;
    delete userEdit;
//    delete passLabel;
//    delete passEdit;
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

    userLabel->setGeometry(20, 70, 350, 30);
    cFont.setPointSize(10);
    cFont.setBold(false);
    userLabel->setFont(cFont);
    userLabel->setText(QStringLiteral("Enter valid email to get code"));

    userEdit->setGeometry(20, 100, 350, 30);
    cFont.setPointSize(10);
    userEdit->setFont(cFont);
    userEdit->setText("");

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


