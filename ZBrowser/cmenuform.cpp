#include "cmenuform.h"
#include "ui_cmenuform.h"

CMenuForm::CMenuForm(QWidget *parent, tgroup &data) :
    QWidget(parent),
    ui(new Ui::CMenuForm)
{
    ui->setupUi(this);
    m_group = data;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
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
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            delete label[i][j];
        }
    }

    delete ui;
}

void CMenuForm::UpdateD(QRect r)
{
    int width = r.width();
    int height = r.height();
    int xOffset = width/5;
    int yOffset = height/5;
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 5; i++){
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
        for(int i = 0; i < 5; i++){
            if (i*5+j < webCount){
                if (websitesList.at(i*5+j)->iconImageCash != 0){
                    label[i][j]->setImage(i, websitesList.at(i*5+j)->iconImage);
                }else{
                    label[i][j]->setImagePathName(i, websitesList.at(i*5+j)->icon);
                    websitesList.at(i*5+j)->iconImageCash = 1;
                    websitesList.at(i*5+j)->iconImage = label[i][j]->getImage();
                }
                label[i][j]->setUrl( websitesList.at(i*5+j)->url);
                label[i][j]->setTitleIcon(websitesList.at(i*5+j)->name);
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

