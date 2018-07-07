#include "simagewidget.h"

SImageWidget::SImageWidget(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    setGeometry(0,0,50,50);
}

void SImageWidget::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    iItem = id;
}


void SImageWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawText(QRect(0,0,50,50), QString("Test Tests"));
    if (!bmouseOver) {
        painter.drawImage(QRect(10, 10, 40, 40), QImage(m_pathName));
    }else{
        painter.drawImage(QRect(0, 0, 50, 50), QImage(m_pathName));
    }
    painter.end();
}


void SImageWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void SImageWidget::enterEvent(QEvent * event){
     bmouseOver = true;
     QSound::play(":sound/click.wav");
     repaint();
}
void SImageWidget::leaveEvent(QEvent * event){
     bmouseOver = false;
     repaint();
}

void SImageWidget::mouseReleaseEvent(QMouseEvent * event){
    emit click(iItem);
}
