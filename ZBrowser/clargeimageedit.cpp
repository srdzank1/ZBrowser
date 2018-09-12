#include "clargeimageedit.h"


CLargeImageEdit::CLargeImageEdit(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
  ,m_titleIcon("*")
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_clickedStatus = true;
    m_brush.setColor(Qt::blue);
    setGeometry(0, 0, 200, 200);
    m_imagePlus = QImage(":/res/image/if_plus_1646001.png");
    m_imageMinus = QImage(":/res/image/if_minus_1645995.png");
}

CLargeImageEdit::~CLargeImageEdit()
{

}
void CLargeImageEdit::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    mImage = QImage(pathName).scaled(200, 187, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_Icon = QImage(pathName).scaled(50, 50, Qt::KeepAspectRatio, Qt::FastTransformation);
    iItem = id;
}


void CLargeImageEdit::setImage(int id, QImage & img ){
    mImage = img;
    iItem = id;
}
void CLargeImageEdit::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void CLargeImageEdit::paintEvent(QPaintEvent *event){
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
    if (m_clickedStatus){
        painter.drawImage(QRect(0, 0, 50, 50), m_imagePlus);
    }else{
        painter.drawImage(QRect(0, 0, 50, 50), m_imageMinus);
    }
    painter.end();
}


void CLargeImageEdit::mouseMoveEvent(QMouseEvent *event)
{
}

void CLargeImageEdit::enterEvent(QEvent * event){
    bmouseOver = true;
//     QSound::play(":sound/click.wav");
     repaint();
}
void CLargeImageEdit::leaveEvent(QEvent * event){
    bmouseOver = false;
     repaint();
}

void CLargeImageEdit::mouseReleaseEvent(QMouseEvent * event){
//    emit click(iItem);
    m_clickedStatus = !m_clickedStatus;
    repaint();
    emit clickForUrl(m_url, m_titleIcon, mImage);
    emit clickForEdit(iItem);
}
