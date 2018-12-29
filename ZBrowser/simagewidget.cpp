#include "simagewidget.h"

SImageWidget::SImageWidget(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
  ,m_titleIcon("*")
{
//    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
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
    opt.setAlignment(Qt::AlignTop | Qt::AlignCenter);
    QPen pen;
    painter.setPen(pen);

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

    if ((m_y >= 0 )&&(m_y < 44)){
        scont1 = (float)m_y/44;
    }
    else if ((m_y >= 44 )&&(m_y < 88)){
        scont1 =(float)(88 - m_y)/44;
    }
    else if(m_y > 88){
        scont1 = 0;
    }


    QRect X9( 0, 0, 100, 100);

        if (!bmouseOver) {
            painter.setFont(QFont("Arial", 11, QFont::Normal));
            painter.drawImage(QRect(10, 30, 70, 70), mImage);
        }else{
            if (X9.contains(m_x, m_y)){
                painter.drawImage(QRect(10, 30 -10*scont -10*scont1, 70, 70), mImage);
                if ((scont + scont1) > 0.2){
                    painter.setFont(QFont("Arial", 12, QFont::Bold));
                    pen.setColor(Qt::black);
                    painter.setPen(pen);
                    painter.drawText(QRect(2, 75, 100, 42), m_titleIcon, opt);
                    pen.setColor(Qt::white);
                    painter.setPen(pen);
                    painter.drawText(QRect(0, 77, 100, 42), m_titleIcon, opt);
                }
            }else{
                painter.drawImage(QRect(10, 30, 70, 70), mImage);
            }
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
     repaint();
}
void SImageWidget::leaveEvent(QEvent * event){
     bmouseOver = false;
     repaint();
}

void SImageWidget::mouseReleaseEvent(QMouseEvent * event){
    emit click(iItem);
}
