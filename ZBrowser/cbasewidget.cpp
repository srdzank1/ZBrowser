#include "cbasewidget.h"


CBaseWidget::CBaseWidget(QWidget *parent) : QWidget(parent)
  ,iItem(0)
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
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, 50, 50), mImage);
    painter.end();
}


void CBaseWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void CBaseWidget::enterEvent(QEvent * event){

}
void CBaseWidget::leaveEvent(QEvent * event){

}

void CBaseWidget::mouseReleaseEvent(QMouseEvent * event){
}
