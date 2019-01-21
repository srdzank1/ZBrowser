#include "cmessagedialog.h"

CMessageDialog::CMessageDialog(QWidget *parent) : QWidget(parent)
{
    l = new QLabel(this);
    MsgLabel = new QLabel(this);
    okButton = new QPushButton(this);
}

CMessageDialog::~CMessageDialog()
{
    delete l;
    delete MsgLabel;
    delete okButton;

}

void CMessageDialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();
}

void CMessageDialog::dialogSettings(const QString& title, const QString& info){
    QFont cFont;

    l = new QLabel(this);
    l->setGeometry(20,10, 300, 30);
    cFont.setPointSize(16);
    cFont.setBold(true);
    l->setFont(cFont);
    l->setText(title);

    //----------------------------------------------------

    MsgLabel->setGeometry(20, 50, 360, 110);
    cFont.setPointSize(10);
    cFont.setBold(false);
    MsgLabel->setFont(cFont);
    MsgLabel->setText(info);

    okButton->setGeometry( QRect(20 , 170, 100 ,30));
    cFont.setPointSize(10);
    cFont.setBold(true);
    okButton->setFont(cFont);
    okButton->setText(QStringLiteral("Ok"));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(procOk(bool)));
    okButton->show();
}

void CMessageDialog::procOk(bool stat){
    emit clickOK();
}



