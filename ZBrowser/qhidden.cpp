#include "qhidden.h"

QHidden::QHidden(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
}


void QHidden::enterEvent(QEvent * event){
    emit showStatus(true);
}
void QHidden::leaveEvent(QEvent * event){
    emit showStatus(false);
}
