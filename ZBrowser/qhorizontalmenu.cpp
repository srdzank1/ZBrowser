#include "qhorizontalmenu.h"
#include "ui_qhorizontalmenu.h"


QHorizontalMenu::QHorizontalMenu(QWidget *parent, tgroup &data) :
    QWidget(parent),
    ui(new Ui::QHorizontalMenu)
{
    ui->setupUi(this);
    m_group = data;
    catwegoryCount = m_group.categories.count();

    for(int i = 0; i < catwegoryCount; i++){
        imageItem[i] = new SImageWidget(this);
        imageItem[i]->resize(QSize(50, 50));
        imageItem[i]->repaint();
        connect(imageItem[i], SIGNAL(click(int)), this, SLOT(processClick(int)));
    }
    update();
}

void QHorizontalMenu::processClick(int i){
    emit click(i);
}

QHorizontalMenu::~QHorizontalMenu()
{
    for(int i = 0; i < catwegoryCount; i++){
        delete imageItem[i];
    }
    delete ui;
}

void QHorizontalMenu::UpdateD(QRect r)
{
    int width = r.width()-200;
    int cellWidth = width / catwegoryCount;

    int catwegoryCount = m_group.categories.count();

    for(int i = 0; i < catwegoryCount; i++){
        tcategory *item =  m_group.categories.at(i);
//        int i1 = i +1;
//        QRect r1 = QRect(width/catwegoryCount * i1, 0,width/catwegoryCount * i1+ 100, 120);
        QRect r1 = QRect(100 + cellWidth * i, 0, cellWidth, 120);

        imageItem[i]->setGeometry(r1);
        QString iconPath = QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ item->icon);
        imageItem[i]->setImagePathName(i, iconPath);
        imageItem[i]->setTitleIcon(item->name);
    }
}

