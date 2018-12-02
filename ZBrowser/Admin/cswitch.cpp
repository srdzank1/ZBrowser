#include "cswitch.h"

CSwitch::CSwitch(QWidget *parent) : QWidget(parent)
{
    mOnImage = QImage(QStringLiteral(":/res/image/on-sliders.png"));
    mOffImage = QImage(QStringLiteral(":/res/image/off-sliders.png"));
    statOn = false;
}

void CSwitch::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if (statOn == true){
        painter.drawImage(QRect(0,0, width(),height()), mOnImage);
    }else{
        painter.drawImage(QRect(0,0, width(),height()), mOffImage);
    }
    painter.end();

}

void CSwitch::mouseReleaseEvent(QMouseEvent * event){
    if (event->pos().x() <= 50){
        statOn = true;
    }else{
        statOn = false;
    }
    emit changeSwitchStatus(statOn);
    emit changeEnableRestriction();
    emit changeEnableSchedule();
    repaint();
}

