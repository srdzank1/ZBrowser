#include "cheaderimageinfo.h"


CHeaderImageInfo::CHeaderImageInfo(QWidget *parent) : QWidget(parent)
  ,iItem(0)
{
//    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_brush.setColor(Qt::blue);
    mAnimate = false;
}

CHeaderImageInfo::~CHeaderImageInfo()
{

}

void CHeaderImageInfo::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    mImage = QImage(pathName).scaled(200, 187, Qt::KeepAspectRatio, Qt::FastTransformation);;
    iItem = id;
}


void CHeaderImageInfo::setImage(int id, QImage & img ){
    mImage = img;
    iItem = id;
}

void CHeaderImageInfo::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void CHeaderImageInfo::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if (mAnimate == false){
    QTextOption opt;
    QPen pen;
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawImage(QRect(0, 0, m_width, m_height), mImage);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawText(QRect(71, 19, 300,50), m_titleIcon, opt);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawText(QRect(70, 20, 300, 50), m_titleIcon, opt);

    }else{
        if (onEnter == true){
            QTextOption opt;
            QPen pen;
            painter.setFont(QFont("Arial", 12, QFont::Bold));
            painter.drawImage(QRect(2, 2, m_width-2, m_height-2), mImage);
            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawText(QRect(71, 19, 300,50), m_titleIcon, opt);
            pen.setColor(Qt::white);
            painter.setPen(pen);
            painter.drawText(QRect(70, 20, 300, 50), m_titleIcon, opt);

        }else{
            QTextOption opt;
            QPen pen;
            painter.setFont(QFont("Arial", 12, QFont::Bold));
            painter.drawImage(QRect(0, 0, m_width, m_height), mImage);
            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawText(QRect(71, 19, 300,50), m_titleIcon, opt);
            pen.setColor(Qt::white);
            painter.setPen(pen);
            painter.drawText(QRect(70, 20, 300, 50), m_titleIcon, opt);
        }
    }
    painter.end();
}


void CHeaderImageInfo::mouseMoveEvent(QMouseEvent *event)
{

}

void CHeaderImageInfo::enterEvent(QEvent * event){
    if (mAnimate == true){
        onEnter = true;
        repaint();
    }
}
void CHeaderImageInfo::leaveEvent(QEvent * event){
    if (mAnimate == true){
        onEnter = false;
        repaint();
    }
}

void CHeaderImageInfo::mouseReleaseEvent(QMouseEvent * event){
    buttonClick();
}
