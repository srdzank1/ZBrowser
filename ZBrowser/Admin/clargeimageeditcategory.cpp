#include "Admin/clargeimageeditcategory.h"


CLargeImageEditCategory::CLargeImageEditCategory(QWidget *parent) : QWidget(parent)
  ,bmouseOver(false)
  ,iItem(0)
  ,m_titleIcon("*")
{
//    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_clickedStatus = true;
    m_brush.setColor(Qt::blue);
    setGeometry(0, 0, 200, 200);
    m_imagePlus = QImage(":/res/image/if_plus_1646001.png");
    m_imageMinus = QImage(":/res/image/if_minus_1645995.png");
}

CLargeImageEditCategory::~CLargeImageEditCategory()
{

}
void CLargeImageEditCategory::setImagePathName(int id, const QString& pathName){
    m_pathName = pathName;
    mImage = QImage(pathName).scaled(200, 187, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_Icon = QImage(pathName).scaled(50, 50, Qt::KeepAspectRatio, Qt::FastTransformation);
    iItem = id;
}


void CLargeImageEditCategory::setImage(int id, QImage & img ){
    mImage = img;
    iItem = id;
}
void CLargeImageEditCategory::setTitleIcon(const QString& name){
    m_titleIcon = name;
}

void CLargeImageEditCategory::paintEvent(QPaintEvent *event){
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
        if (m_clickedStatus){
            painter.drawImage(QRect(35, 25, 40, 40), m_imagePlus);
        }else{
            painter.drawImage(QRect(35, 25, 40, 40), m_imageMinus);
        }


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

        if (m_clickedStatus){
            painter.drawImage(QRect(20, 20, 50, 50), m_imagePlus);
        }else{
            painter.drawImage(QRect(20, 20, 50, 50), m_imageMinus);
        }

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


void CLargeImageEditCategory::mouseMoveEvent(QMouseEvent *event)
{
}

void CLargeImageEditCategory::enterEvent(QEvent * event){
     bmouseOver = true;
     repaint();
}
void CLargeImageEditCategory::leaveEvent(QEvent * event){
     bmouseOver = false;
     repaint();
}

void CLargeImageEditCategory::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
    {
        m_clickedStatus = !m_clickedStatus;
        repaint();
        emit updateHorizontalMenu();
    }
}


void CLargeImageEditCategory::mouseReleaseEvent(QMouseEvent * event){
//    emit click(iItem);
//    m_clickedStatus = !m_clickedStatus;
//    repaint();
//    emit clickForUrl(m_url, m_titleIcon, mImage);
    emit clickForEdit(iItem);
}
