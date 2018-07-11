#include "ccentralbackgroundimage.h"

CCentralBackgroundImage::CCentralBackgroundImage(QWidget *parent) : QWidget(parent)
  ,iItem(0)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_brush.setColor(Qt::blue);
}

CCentralBackgroundImage::~CCentralBackgroundImage()
{

}

void CCentralBackgroundImage::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    mImage = QImage(pathName).scaled(200, 187, Qt::KeepAspectRatio, Qt::FastTransformation);;
    iItem = id;
}


void CCentralBackgroundImage::setImage(int id, QImage & img ){
    mImage = img;
    iItem = id;
}

void CCentralBackgroundImage::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, m_width, m_height), mImage);
    painter.end();
}


void CCentralBackgroundImage::mouseMoveEvent(QMouseEvent *event)
{

}

void CCentralBackgroundImage::enterEvent(QEvent * event){
     repaint();
}
void CCentralBackgroundImage::leaveEvent(QEvent * event){
     repaint();
}

void CCentralBackgroundImage::mouseReleaseEvent(QMouseEvent * event){
}
