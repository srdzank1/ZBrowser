#include "ccategorylistitems.h"

CCategoryListItems::CCategoryListItems(tgroup &data, QWidget *parent) : QWidget(parent)
{
    m_group = data;
    xOffset = 200;
    yOffset = 187;
}


void CCategoryListItems::createCategoryMenuItems(int id){
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
                pLargeImage->setId(websitesList.at(j*iMax+i)->id);
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
}

void CCategoryListItems::getHideStatus(tfilterwebsite &mFilterData){
    QMap<QString, QString> map;
    for(int ia = 0; ia < mFilterData.count(); ia++){
        map.insert(mFilterData.at(ia), mFilterData.at(ia));
    }

    for (int i = 0; i < pListLargeImage.count(); i++){
        if (map[pListLargeImage.at(i)->getId()] == pListLargeImage.at(i)->getId()){
            for (int id = 0; id < mFilterData.count(); id ++){
                if (mFilterData.at(id)==pListLargeImage.at(i)->getId()){
                    mFilterData.removeAt(id);
                }
            }
        }
    }

    for (int i = 0; i < pListLargeImage.count(); i++){
        if(!pListLargeImage.at(i)->getStatus()){
            mFilterData.push_back(pListLargeImage.at(i)->getId());
        }
    }
}

void CCategoryListItems::setHideStatus(tfilterwebsite &mFilterData){
    QMap<QString, QString> map;
    for(int ia = 0; ia < mFilterData.count(); ia++){
        map.insert(mFilterData.at(ia), mFilterData.at(ia));
    }
    for (int i = 0; i < pListLargeImage.count(); i++){
        if (map[pListLargeImage.at(i)->getId()] == pListLargeImage.at(i)->getId()){
            pListLargeImage.at(i)->setStatus(false);
        }
    }
}


