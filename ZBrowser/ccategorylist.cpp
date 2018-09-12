#include "ccategorylist.h"

CCategoryList::CCategoryList(tgroup &data, QWidget *parent) : QWidget(parent)
{
    m_group = data;
    xOffset = 200;
    yOffset = 187;
}

void CCategoryList::paintEvent(QPaintEvent *event){
//    QPainter painter(this);
//    QPainterPath path;

//        path.addRoundedRect(QRectF(0, 0, geometry().width(), geometry().height()), 10, 10);
//        QPen pen(Qt::darkYellow, 10);
//        painter.setPen(pen);
//        painter.fillPath(path, Qt::white);
//        painter.drawPath(path);

//    painter.end();

}

void CCategoryList::createCategoryMenu(int id){
 //   setUpdatesEnabled(false);
    m_width = geometry().width();
    m_height = geometry().height();

    int marX;
    int marY;
    marX = geometry().left();
    marY = geometry().top();
    for (int i = 0; i < pListLargeImage.count(); i++){
            delete pListLargeImage.at(i);
    }

    pListLargeImage.clear();
    int catCount = m_group.categories.count();
    int iMax = 1;
    int jMax = catCount / iMax + 1;

//    int iMax = (int)m_width / xOffset;
//    int jMax = webCount / iMax + 1;
    mRowCount = jMax;
    for(int j = 0; j < jMax; j++){
        for(int i = 0; i < iMax; i++){
            if (j*iMax+i < catCount){

                pLargeImage = new CLargeImageEdit(this);
                pLargeImage->resize(QSize(0, 0));
                connect(pLargeImage, SIGNAL(click(int)), this, SLOT(processClick(int)));
                connect(pLargeImage, SIGNAL(clickForEdit(int&)), this, SLOT(processClickForEdit(int&)));

                QRect r1 = QRect( xOffset* i, yOffset* j , xOffset , yOffset);

                pLargeImage->setGeometry(r1);
                pLargeImage->setWidth(xOffset);
                pLargeImage->setHeight(yOffset);

                pLargeImage->setImagePathName(j*iMax+i, m_group.categories.at(j*iMax+i)->icon);

                pLargeImage->setTitleIcon(m_group.categories.at(j*iMax+i)->name);
                pListLargeImage.push_back(pLargeImage);
                pLargeImage->repaint();
                pLargeImage = 0;

            }else{
                continue;
            }
        }

        setGeometry(0, 0, (iMax) * xOffset, (j+5.5) * yOffset);
    }
    update();
//   setUpdatesEnabled(true);
}


void CCategoryList::processClickForEdit(int& i){
    emit clickForEdit(i);
}
