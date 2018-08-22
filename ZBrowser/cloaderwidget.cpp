#include "cloaderwidget.h"

CLoaderWidget::CLoaderWidget(QWidget *parent) : QWidget(parent)
{

}

CLoaderWidget::~CLoaderWidget()
{

}

void CLoaderWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen p;
    p.setColor(Qt::red);
    painter.setPen(p);
    painter.drawLine(0, 1, width()*(double(m_value)/100.f), 1);
    painter.drawLine(0, 2, width()*(double(m_value)/100.f), 2);
    p.setColor(Qt::darkRed);
    painter.setPen(p);
    painter.drawLine(0, 3, width()*(double(m_value)/100.f), 3);
    p.setColor(Qt::red);
    painter.setPen(p);
    painter.drawLine(0, 4, width()*(double(m_value)/100.f), 4);
    p.setColor(Qt::lightGray);
    painter.setPen(p);
    painter.drawLine(0, 5, width()*(double(m_value)/100.f), 5);

    painter.end();

}




