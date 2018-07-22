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

void CMenuForm::createMenuByCategory(int id){
 //   setUpdatesEnabled(false);


    for (int i = 0; i < pListLargeImage.count(); i++){
            delete pListLargeImage.at(i);
    }

    pListLargeImage.clear();
    tcategory* currentCategory =  m_group.categories.at(id);
    QList<twebsite*> websitesList = currentCategory->websites;
    int webCount = websitesList.count();
    int iMax = (int)m_width / xOffset;
    int jMax = webCount / iMax + 1;
    for(int j = 0; j < jMax; j++){
        for(int i = 0; i < iMax; i++){
            if (j*jMax+i < webCount){

                pLargeImage = new CLargeImage(this);
                pLargeImage->resize(QSize(0, 0));
                pLargeImage->repaint();
                connect(pLargeImage, SIGNAL(click(int)), this, SLOT(processClick(int)));
                connect(pLargeImage, SIGNAL(clickForUrl(QString&)), this, SLOT(processClickForUrl(QString&)));

                QRect r1 = QRect( xOffset* i, yOffset* j , xOffset * (i+1) , yOffset * (j + 1));
                pLargeImage->setGeometry(r1);
                pLargeImage->setWidth(xOffset);
                pLargeImage->setHeight(yOffset);


                if (websitesList.at(j*jMax+i)->iconImageCash != 0){
                    pLargeImage->setImage(i, websitesList.at(j*jMax+i)->iconImage);
                }else{
                    pLargeImage->setImagePathName(i, websitesList.at(j*jMax+i)->icon);
                    websitesList.at(j*jMax+i)->iconImageCash = 1;
                    websitesList.at(j*jMax+i)->iconImage = pLargeImage->getImage();
                }
                pLargeImage->setUrl( websitesList.at(j*jMax+i)->url);
                pLargeImage->setTitleIcon(websitesList.at(j*jMax+i)->name);
                pListLargeImage.push_back(pLargeImage);
                pLargeImage = 0;

            }else{
                continue;
            }
        }

        setGeometry(0, 0, (iMax) * xOffset, (j+5.5) * yOffset);
    }
//   setUpdatesEnabled(true);
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

void CMenuForm::processClick(int i){
//    close();
}

void CMenuForm::processClickForUrl(QString& url){
   emit clickForUrl(url);
}

