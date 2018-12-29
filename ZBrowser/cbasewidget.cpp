#include "cbasewidget.h"


CBaseWidget::CBaseWidget(QWidget *parent) : QWidget(parent)
  ,iItem(0)
  ,bmouseOver(false)
  ,bmouseClick(false)
{
//    setAttribute(Qt::WA_StaticContents);
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


void CBaseWidget::setImage(int id, QImage & img, QImage & img_roll, QImage & img_click ){
    mImage = img;
    mImage_rollover = img_roll;
    mImage_click = img_click;

    iItem = id;
}

void CBaseWidget::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void CBaseWidget::paintEvent(QPaintEvent *event){
    QPainterPath path;

    if (bmouseOver){
        if (bmouseClick){
            QPainter painter(this);
            painter.drawImage(QRect(0, 0, 50, 50), mImage_click);
            painter.end();
            bmouseClick = false;
        }else{
            QPainter painter(this);
            painter.drawImage(QRect(0, 0, 50, 50), mImage_rollover);
            painter.end();
        }
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
     QSound::play(":sound/click.wav");
    repaint();
}
void CBaseWidget::leaveEvent(QEvent * event){
    bmouseOver = false;
     QSound::play(":sound/click.wav");
    repaint();
}

void CBaseWidget::mouseReleaseEvent(QMouseEvent * event){
    emit buttonClick();
}

void CBaseWidget::mousePressEvent(QMouseEvent * event){
    bmouseClick = true;
    QSound::play(":sound/click.wav");
    repaint();
}
