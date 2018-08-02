#include "cbasewidget.h"


CBaseWidget::CBaseWidget(QWidget *parent) : QWidget(parent)
  ,iItem(0)
  ,bmouseOver(false)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_brush.setColor(Qt::blue);
}

CBaseWidget::~CBaseWidget()
{

}

void CBaseWidget::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    mImage = QImage(pathName).scaled(200, 187, Qt::KeepAspectRatio, Qt::FastTransformation);;
    iItem = id;
}


void CBaseWidget::setImage(int id, QImage & img ){
    mImage = img;
    iItem = id;
}

void CBaseWidget::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void CBaseWidget::paintEvent(QPaintEvent *event){
    QPainterPath path;

    if (bmouseOver){
        QPainter painter(this);
        QBrush brush(Qt::white);
        painter.setBrush(brush);
        painter.drawEllipse(QPointF(25,25), 25, 25);

        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

        painter.drawImage(QRect(5, 5, 40, 40), mImage);
        painter.end();
    }else{
        QPainter painter(this);
        painter.drawImage(QRect(0, 0, 50, 50), mImage);
        painter.end();
    }
}


void CBaseWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void CBaseWidget::enterEvent(QEvent * event){
    bmouseOver = true;
//     QSound::play(":sound/click.wav");
    repaint();
}
void CBaseWidget::leaveEvent(QEvent * event){
    bmouseOver = false;
//     QSound::play(":sound/click.wav");
    repaint();
}

void CBaseWidget::mouseReleaseEvent(QMouseEvent * event){
    emit buttonClick();
}

