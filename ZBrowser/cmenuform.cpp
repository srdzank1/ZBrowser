#include "cmenuform.h"
#include "ui_cmenuform.h"

CMenuForm::CMenuForm(QWidget *parent, tgroup &data, int &width, int&height) :
    QWidget(parent),
    ui(new Ui::CMenuForm)
{
    ui->setupUi(this);
    pLargeImage =0;
    m_group = data;
    m_width = width;
    m_height = height;
    int xOffset = 200;
    int yOffset = 187;
    update();
}

CMenuForm::~CMenuForm()
{
    QList<CLargeImage*>::iterator it;
    for (it =pListLargeImage.begin(); it != pListLargeImage.end(); it++){
         delete *it;
    }
    pListLargeImage.clear();
    CLargeImage * pLargeImage;
    delete ui;
}

void CMenuForm::UpdateD(QRect r)
{
    int width = r.width();
    int height = r.height();
    xOffset = 200; //width/5;
    yOffset = 187; //height/5;

}

void CMenuForm::createMenuByCategory(int id, tfilterwebsite &mFilterData, tsettings &mSettings){

    for (int i = 0; i < pListLargeImage.count(); i++){
            delete pListLargeImage.at(i);
    }

    pListLargeImage.clear();
    tcategory* currentCategory =  m_group.categories.at(id);
    QList<twebsite*> websitesList;
    QList<twebsite*> websitesListR;
    QList<twebsite*>::iterator it2;

    if(mSettings.enableRestriction == true){
        websitesListR = currentCategory->websites;
        QMap<QString, QString> map;
        for(int ia = 0; ia < mFilterData.count(); ia++){
            map.insert(mFilterData.at(ia), mFilterData.at(ia));
        }

        for (it2 = websitesListR.begin(); it2  != websitesListR.end(); it2++){
            twebsite* item = (*it2);
            if (!map.contains(item->id)){
                websitesList.append((*it2));
            }
        }
    }else{
        websitesList = currentCategory->websites;
    }

    int webCount = websitesList.count();

    int iMax = (int)m_width / xOffset;
    int jMax = webCount / iMax + 1;

    mRowCount = jMax;
    for(int j = 0; j < jMax; j++){
        for(int i = 0; i < iMax; i++){
            if (j*iMax+i < webCount){
                pLargeImage = new CLargeImage(this);
                pLargeImage->resize(QSize(0, 0));
                pLargeImage->repaint();
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
                pLargeImage->setUrl( websitesList.at(j*iMax+i)->url);
                pLargeImage->setTitleIcon(websitesList.at(j*iMax+i)->name);
                pListLargeImage.push_back(pLargeImage);
                pLargeImage = 0;

            }else{
                continue;
            }
        }

        setGeometry(0, 0, (iMax) * xOffset, (j+5.5) * yOffset);
    }
}

bool CMenuForm::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Escape) {
            close();
            return true;
        }
    }
    return QWidget::event(event);
}


void CMenuForm::processClickForUrl(QString& url, QString& title, QImage& img ){
    QString pathFile = QDir::toNativeSeparators(QDir::currentPath() +"/sounds/click.wav");
    QSound::play(pathFile);
    emit clickForUrl(url, title, img);
}

