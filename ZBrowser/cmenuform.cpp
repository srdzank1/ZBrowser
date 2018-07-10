#include "cmenuform.h"
#include "ui_cmenuform.h"

CMenuForm::CMenuForm(QWidget *parent, tgroup &data) :
    QWidget(parent),
    ui(new Ui::CMenuForm)
{
    ui->setupUi(this);
    m_group = data;
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 8; i++){
            label[i][j] = new CLargeImage(this);
            label[i][j]->resize(QSize(0, 0));
            label[i][j]->repaint();
            connect(label[i][j], SIGNAL(click(int)), this, SLOT(processClick(int)));
            connect(label[i][j], SIGNAL(clickForUrl(QString&)), this, SLOT(processClickForUrl(QString&)));
        }
    }
    update();

}

CMenuForm::~CMenuForm()
{
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 8; i++){
            delete label[i][j];
        }
    }

    delete ui;
}

void CMenuForm::UpdateD(QRect r)
{
    int width = r.width();
    int height = r.height();
    int xOffset = 200; //width/5;
    int yOffset = 187; //height/5;
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 8; i++){
            QRect r1 = QRect( xOffset* i, yOffset* j , xOffset * (i+1) , yOffset * (j + 1));
            label[i][j]->setGeometry(r1);
            label[i][j]->setWidth(xOffset);
            label[i][j]->setHeight(yOffset);
        }
    }
}

void CMenuForm::createMenuByCategory(int id){

    tcategory* currentCategory =  m_group.categories.at(id);
    QList<twebsite*> websitesList = currentCategory->websites;
    int webCount = websitesList.count();
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 8; i++){
            if (j*5+i < webCount){
                if (websitesList.at(j*5+i)->iconImageCash != 0){
                    label[i][j]->setImage(i, websitesList.at(j*5+i)->iconImage);
                }else{
                    label[i][j]->setImagePathName(i, websitesList.at(j*5+i)->icon);
                    websitesList.at(i*5+j)->iconImageCash = 1;
                    websitesList.at(i*5+j)->iconImage = label[i][j]->getImage();
                }
                label[i][j]->setUrl( websitesList.at(j*5+i)->url);
                label[i][j]->setTitleIcon(websitesList.at(j*5+i)->name);
            }else{
                label[i][j]->setImagePathName(i, "");

            }
        }
         repaint();
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

void CMenuForm::processClick(int i){
//    close();
}

void CMenuForm::processClickForUrl(QString& url){
   emit clickForUrl(url);
}

