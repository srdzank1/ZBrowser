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
        }
    }
    update();

}

CMenuForm::~CMenuForm()
{
    delete ui;
}

void CMenuForm::UpdateD(QRect r)
{
    int width = r.width();
    int height = r.height();
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            QRect r1 = QRect(width/5 * i, height/5 * j ,width/1 * i+ 180, height/1 * j + 180);
            label[i][j]->setGeometry(r1);
        }
    }
}

void CMenuForm::createMenuByCategory(int id){

    tcategory* currentCategory =  m_group.categories.at(id);
    QList<twebsite*> websitesList = currentCategory->websites;
    int webCount = websitesList.count();
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if (i*j < webCount){
                QString iconPath = QDir::toNativeSeparators(QDir::currentPath() +"/"+ websitesList.at(i*5+j)->icon);
                label[i][j]->setImagePathName(i, iconPath);
//                label[i][j]->setUrl(i, websitesList.at(i*5+j));

            }else{
                label[i][j]->setImagePathName(i, "");
            }

        }
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
    close();
}
