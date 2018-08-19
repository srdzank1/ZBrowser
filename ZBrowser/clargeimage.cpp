#include "clargeimage.h"

CLargeImage::CLargeImage(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
  ,m_titleIcon("*")
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_brush.setColor(Qt::blue);
}

CLargeImage::~CLargeImage()
{

}
void CLargeImage::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    mImage = QImage(pathName).scaled(200, 187, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_Icon = QImage(pathName).scaled(50, 50, Qt::KeepAspectRatio, Qt::FastTransformation);
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
    QPainterPath path;

    if (bmouseOver) {
        path.addRoundedRect(QRectF(30, 20, m_width-60, m_height-65), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

        pen.setColor(Qt::black);
        painter.setPen(pen);

        painter.setFont(QFont("Arial", 11, QFont::Bold));
        painter.drawImage(QRect(30, 20, m_width-60, m_height-65), mImage);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(QRect(10, m_height-87, m_width-10, m_height-67), m_titleIcon, opt);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(QRect(8, m_height-85, m_width-10, m_height-65), m_titleIcon, opt);

    }else{
        path.addRoundedRect(QRectF(10, 10, m_width-20, m_height-30), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::red);
        painter.drawPath(path);

        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.setFont(QFont("Arial", 11, QFont::Normal));
        painter.drawImage(QRect(10, 10, m_width-20, m_height-30), mImage);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(QRect(10, m_height-77, m_width-10, m_height-57), m_titleIcon, opt);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(QRect(8, m_height-75, m_width-10, m_height-55), m_titleIcon, opt);
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
//    emit click(iItem);
    emit clickForUrl(m_url, m_titleIcon, mImage);
}
