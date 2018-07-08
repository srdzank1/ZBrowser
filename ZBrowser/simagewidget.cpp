#include "simagewidget.h"

SImageWidget::SImageWidget(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
  ,m_titleIcon("*")
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    setGeometry(0,0,0,0);
}

void SImageWidget::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    iItem = id;
}

void SImageWidget::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void SImageWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);

    if (!bmouseOver) {
        painter.setFont(QFont("Arial", 9, QFont::Normal));
        painter.drawImage(QRect(20, 30, 40, 40), QImage(m_pathName));
        painter.drawText(QRect(0,0,80,35), m_titleIcon, opt);
    }else{
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawImage(QRect(10, 30, 60, 50), QImage(m_pathName));
        painter.drawText(QRect(0,0,80,35), m_titleIcon, opt);
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
