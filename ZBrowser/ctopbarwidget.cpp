#include "ctopbarwidget.h"

CTopBarWidget::CTopBarWidget(QWidget *parent) : QWidget(parent)
{

}

CTopBarWidget::~CTopBarWidget()
{

}

void CTopBarWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen p;
    p.setColor(Qt::gray);
    painter.setPen(p);
    for (int i = 0; i < 48; i++){
        painter.drawLine(0, i, width(), i);
    }
    p.setColor(Qt::darkGray);
    painter.setPen(p);
    painter.drawLine(0, 48, width(), 48);
    painter.drawLine(0, 49, width(), 49);
    painter.drawLine(0, 50, width(), 50);

    painter.end();

}
