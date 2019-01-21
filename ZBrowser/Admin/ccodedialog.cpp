#include "ccodedialog.h"

CCodeDialog::CCodeDialog(QWidget *parent) : QWidget(parent)
{
    userLabel = new QLabel(this);
    userEdit = new QLineEdit(this);

    okButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    AskCodeButton = new QPushButton(this);
    userEdit->setFocus();
}

CCodeDialog::~CCodeDialog()
{
    delete userLabel;
    delete userEdit;
    delete okButton;
    delete cancelButton;
    delete AskCodeButton;
}

void CCodeDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();
}

void CCodeDialog::dialogSettings(){
    QFont cFont;

    l = new QLabel(this);
    l->setGeometry(20,10, 300, 30);
    cFont.setPointSize(16);
    cFont.setBold(true);
    l->setFont(cFont);
    l->setText(QStringLiteral("Validate Code"));

    //----------------------------------------------------

    userLabel->setGeometry(20, 50, 120, 30);
    cFont.setPointSize(10);
    cFont.setBold(false);
    userLabel->setFont(cFont);
    userLabel->setText(QStringLiteral("Enter code "));

    userEdit->setGeometry(160, 50, 250, 30);
    cFont.setPointSize(10);
    userEdit->setFont(cFont);
    userEdit->setText("");

//------------------------------------------------------------------------

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

    AskCodeButton->setGeometry( QRect(220 , 170, 150 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    AskCodeButton->setFont(cFont);
    AskCodeButton->setText(QStringLiteral("Ask new code"));
    connect(AskCodeButton, SIGNAL(clicked(bool)), this, SLOT(procAskCode(bool)));
    AskCodeButton->show();

}

void CCodeDialog::procOk(bool stat){
    emit clickOK();
}

void CCodeDialog::procCancel(bool stat){
    emit clickCancel();
}


void CCodeDialog::procAskCode(bool stat){
    emit clickAskCode();
}

