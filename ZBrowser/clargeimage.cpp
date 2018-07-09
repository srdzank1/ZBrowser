#include "clargeimage.h"

CLargeImage::CLargeImage(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
  ,m_titleIcon("*")
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
}

void CLargeImage::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    mImage = QImage(m_pathName);
    iItem = id;
}


void CLargeImage::setImage(int id, QImage & img ){
    mImage = img;
    iItem = id;
}
void CLargeImage::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void CLargeImage::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);

    if (!bmouseOver) {
        painter.setFont(QFont("Arial", 11, QFont::Normal));
        painter.drawImage(QRect(20, 40, m_width-40, m_height-50), mImage);
        painter.drawText(QRect(10, 0, m_width-10, 40), m_titleIcon, opt);
    }else{
        painter.setFont(QFont("Arial", 13, QFont::Bold));
        painter.drawImage(QRect(10, 30, m_width-20, m_height-30), mImage);
        painter.drawText(QRect(10, 0, m_width-10, 40), m_titleIcon, opt);
    }
    painter.end();
}


void CLargeImage::mouseMoveEvent(QMouseEvent *event)
{

}

void CLargeImage::enterEvent(QEvent * event){
     bmouseOver = true;
//     QSound::play(":sound/click.wav");
     repaint();
}
void CLargeImage::leaveEvent(QEvent * event){
     bmouseOver = false;
     repaint();
}

void CLargeImage::mouseReleaseEvent(QMouseEvent * event){
    emit click(iItem);
    emit clickForUrl(m_url);
}
