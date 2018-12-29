#include "clargeimage.h"

CLargeImage::CLargeImage(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
  ,m_titleIcon("*")
{
//    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_brush.setColor(Qt::blue);
    setGeometry(0, 0, 200, 200);
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
    QPen pen;
    if (bmouseOver) {

        QPainterPath path;
        path.addRoundedRect(QRectF(30, 20, m_width-60, m_height-65), 30, 30);
        painter.setClipPath(path);
        painter.drawImage(QRect(30, 20, m_width-60, m_height-65), mImage);
        path.addRect(QRectF(0, 0, m_width, m_height));
        painter.setClipPath(path);

        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.setFont(QFont("Arial", 11, QFont::Bold));


        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(QRect(10, m_height-87, m_width-10, m_height-67), m_titleIcon, opt);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(QRect(8, m_height-85, m_width-10, m_height-65), m_titleIcon, opt);

    }else{
        QPainterPath path;
        path.addRoundedRect(QRectF(15, 15, m_width-30, m_height-35), 30, 30);
        painter.setClipPath(path);
        painter.drawImage(QRect(15, 15, m_width-30, m_height-35), mImage);
        path.addRect(QRectF(0, 0, m_width, m_height));
        painter.setClipPath(path);


        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.setFont(QFont("Arial", 11, QFont::Normal));

        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(QRect(10, m_height-77, m_width-10, m_height-55), m_titleIcon, opt);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(QRect(8, m_height-75, m_width-10, m_height-53), m_titleIcon, opt);


    }
    painter.end();
}


void CLargeImage::mouseMoveEvent(QMouseEvent *event)
{
}

void CLargeImage::enterEvent(QEvent * event){
    bmouseOver = true;
    repaint();
}
void CLargeImage::leaveEvent(QEvent * event){
    bmouseOver = false;
    repaint();
}

void CLargeImage::mouseReleaseEvent(QMouseEvent * event){
    emit clickForUrl(m_url, m_titleIcon, mImage);
    emit clickForEdit(iItem);
}
