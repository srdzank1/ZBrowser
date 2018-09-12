#include "ccategorylistitems.h"

CCategoryListItems::CCategoryListItems(tgroup &data, QWidget *parent) : QWidget(parent)
{
    m_group = data;
    xOffset = 200;
    yOffset = 187;
}

void CCategoryListItems::paintEvent(QPaintEvent *event){
//    QPainter painter(this);
//    QPainterPath path;

//        path.addRoundedRect(QRectF(0, 0, geometry().width(), geometry().height()), 10, 10);
//        QPen pen(Qt::darkYellow, 10);
//        painter.setPen(pen);
//        painter.fillPath(path, Qt::white);
//        painter.drawPath(path);

//    painter.end();

}

void CCategoryListItems::createCategoryMenuItems(int id){
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
    tcategory* currentCategory =  m_group.categories.at(id);
    QList<twebsite*> websitesList = currentCategory->websites;
    int webCount = websitesList.count();
    int iMax = (int)m_width / xOffset;
    int jMax = webCount / iMax + 1;
    mRowCount = jMax;
    for(int j = 0; j < jMax; j++){
        for(int i = 0; i < iMax; i++){
            if (j*iMax+i < webCount){

                pLargeImage = new CLargeImageEdit(this);
                pLargeImage->resize(QSize(0, 0));
                connect(pLargeImage, SIGNAL(click(int)), this, SLOT(processClick(int)));
                connect(pLargeImage, SIGNAL(clickForUrl(QString&, QString&, QImage&)), this, SLOT(processClickForUrl(QString&, QString&, QImage&)));

                QRect r1 = QRect( xOffset* i, yOffset* j , xOffset , yOffset);
//                QRect r1 = QRect( marX+ xOffset* i, marY+ yOffset* j , xOffset , yOffset);

                pLargeImage->setGeometry(r1);
                pLargeImage->setWidth(xOffset);
                pLargeImage->setHeight(yOffset);


                if (websitesList.at(j*iMax+i)->iconImageCash != 0){
                    pLargeImage->setImage(i, websitesList.at(j*iMax+i)->iconImage);
                }else{
                    pLargeImage->setImagePathName(i, websitesList.at(j*iMax+i)->icon);
                    websitesList.at(j*iMax+i)->iconImageCash = 1;
                    websitesList.at(j*iMax+i)->iconImage = pLargeImage->getImage();
                }
                pLargeImage->setUrl( websitesList.at(j*iMax+i)->url);
                pLargeImage->setTitleIcon(websitesList.at(j*iMax+i)->name);
                pListLargeImage.push_back(pLargeImage);
                pLargeImage->repaint();
                pLargeImage = 0;

            }else{
                continue;
            }
        }

        setGeometry(0, 0, (iMax) * xOffset, (j+1.5) * yOffset);
    }
    update();
//   setUpdatesEnabled(true);
}
