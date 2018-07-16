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
    mImage = QImage(m_pathName);
}

void SImageWidget::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void SImageWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QTextOption opt;
    opt.setAlignment(Qt::AlignCenter);
    QPen pen;
    painter.setPen(pen);
    if (!bmouseOver) {
        painter.setFont(QFont("Arial", 11, QFont::Normal));
//        painter.drawImage(QRect(10, 30, 81, 72), mImage);
        painter.drawImage(QRect(10, 30, 76, 72), mImage);
//        painter.drawText(QRect(0,30,100,90), m_titleIcon, opt);
    }else{
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        float scont = 0;
        if ((m_x >= 0 )&&(m_x < 44)){
            scont = (float)m_x/44;
        }
        else if ((m_x >= 44 )&&(m_x < 88)){
            scont =(float)(88 - m_x)/44;
        }
        else if(m_x > 88){
            scont = 0;
        }


        float scont1 = 0;
        if ((m_y >= 0 )&&(m_y < 12)){
            scont1 = (float)m_y/12;
        } else if(m_y >= 12){
            scont1 = 1;
        }


        painter.drawImage(QRect(12, 42 -23*scont -12*scont1, 76, 67), mImage);

//      painter.drawImage(QRect(12, 7, 76, 67), mImage);
//      painter.drawImage(QRect(10, 30, 76, 72), mImage);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(QRect(2, 70, 100,40), m_titleIcon, opt);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(QRect(0, 72, 100,40), m_titleIcon, opt);

    }
    painter.end();
}


void SImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_x = event->x();
    m_y = event->y();
    repaint();
}

void SImageWidget::enterEvent(QEvent * event){
     bmouseOver = true;
//     QSound::play(":sound/click.wav");
     repaint();
}
void SImageWidget::leaveEvent(QEvent * event){
     bmouseOver = false;
     repaint();
}

void SImageWidget::mouseReleaseEvent(QMouseEvent * event){
    emit click(iItem);
}
