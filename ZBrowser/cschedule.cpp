#include "cschedule.h"

CSchedule::CSchedule(tgroup &data, QWidget *parent) : QWidget(parent)
{
    m_group = data;
}

CSchedule::~CSchedule()
{

}

void CSchedule::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, geometry().width(), geometry().height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);
        createForm(painter);
    painter.end();
}

void CSchedule::menuGlobalSettings(){
    editSchedule = new QLabel(this);
    editSchedule->setGeometry(20,15, 300, 30);
    QFont cFont;
    cFont.setPointSize(16);
    cFont.setBold(true);
    editSchedule->setFont(cFont);
    editSchedule->setText(QStringLiteral("Edit schedule"));
}

void CSchedule::createForm(QPainter &painter){
    QPen pen(Qt::darkYellow, 2);
    painter.setPen(pen);
    int hStep = (geometry().height() -160) / 8;
    int wStep = (geometry().width() -40) / 24;
    for (int i = 0; i < 8; i++){
        painter.drawLine(QLineF(20, 80 + i * hStep, geometry().width()-40, 80 + i * hStep));
    }

    for (int i = 0; i < 24; i++){
        painter.drawLine(QLineF(20 + i*wStep, 80 , 20 + i*wStep, geometry().height() -160));
    }
}
