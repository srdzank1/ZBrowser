#include "ccategorylist.h"

CCategoryList::CCategoryList(tgroup &data, QWidget *parent) : QWidget(parent)
{
    m_group = data;
    xOffset = 200;
    yOffset = 187;
}


void CCategoryList::createCategoryMenu(int id){
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

    mRowCount = jMax;
    for(int j = 0; j < jMax; j++){
        for(int i = 0; i < iMax; i++){
            if (j*iMax+i < catCount){

                pLargeImage = new CLargeImageEditCategory(this);
                pLargeImage->resize(QSize(0, 0));
                connect(pLargeImage, SIGNAL(click(int)), this, SLOT(processClick(int)));
                connect(pLargeImage, SIGNAL(clickForEdit(int&)), this, SLOT(processClickForEdit(int&)));
                connect(pLargeImage, SIGNAL(updateHorizontalMenu()), this, SLOT(ProcupdateHorizontalMenu()));
                QRect r1 = QRect( xOffset* i, yOffset* j , xOffset , yOffset);

                pLargeImage->setGeometry(r1);
                pLargeImage->setWidth(xOffset);
                pLargeImage->setHeight(yOffset);

                QString iconPath = QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ m_group.categories.at(j*iMax+i)->icon);
                pLargeImage->setImagePathName(j*iMax+i, iconPath);
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
}


void CCategoryList::processClickForEdit(int& i){
    emit clickForEdit(i);
}

void CCategoryList::getHideStatusCategory(tfiltercategory &mFilterDataCategory){
    QMap<QString, QString> map;
    for(int ia = 0; ia < mFilterDataCategory.count(); ia++){
        map.insert(mFilterDataCategory.at(ia), mFilterDataCategory.at(ia));
    }

    for (int i = 0; i < pListLargeImage.count(); i++){
        if (map[pListLargeImage.at(i)->getId()] == pListLargeImage.at(i)->getId()){
            for (int id = 0; id < mFilterDataCategory.count(); id ++){
                if (mFilterDataCategory.at(id)==pListLargeImage.at(i)->getId()){
                    mFilterDataCategory.removeAt(id);
                }
            }
        }
    }

    for (int i = 0; i < pListLargeImage.count(); i++){
        if(!pListLargeImage.at(i)->getStatus()){
            mFilterDataCategory.push_back(pListLargeImage.at(i)->getId());
        }
    }
}

void CCategoryList::setHideStatusCategory(tfiltercategory &mFilterDataCategory){
    QMap<QString, QString> map;
    for(int ia = 0; ia < mFilterDataCategory.count(); ia++){
        map.insert(mFilterDataCategory.at(ia), mFilterDataCategory.at(ia));
    }
    for (int i = 0; i < pListLargeImage.count(); i++){
        if (map[pListLargeImage.at(i)->getId()] == pListLargeImage.at(i)->getId()){
            pListLargeImage.at(i)->setStatus(false);
        }
    }
}

void CCategoryList::ProcupdateHorizontalMenu(){
    emit updateHorizontalMenu();
}
