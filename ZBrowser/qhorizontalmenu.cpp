#include "qhorizontalmenu.h"
#include "ui_qhorizontalmenu.h"


QHorizontalMenu::QHorizontalMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHorizontalMenu)
{

    ui->setupUi(this);


    //Create 10 labels to populate the menu


    for(int i = 0; i < 10; i++){
        label[i] = new SImageWidget(this);
        label[i]->resize(QSize(50, 50));
        label[i]->repaint();
        connect(label[i], SIGNAL(click(int)), this, SLOT(processClick(int)));
    }
    update();
    //show the menu
}

void QHorizontalMenu::processClick(int i){
    emit click(i);
}


QHorizontalMenu::~QHorizontalMenu()
{
    delete ui;
}

void QHorizontalMenu::UpdateD(QRect r)
{
    int width = r.width();

    for(int i = 0; i < 10; i++){
        int i1 = i +1;
        QRect r1 = QRect(width/11 * i1, 0,width/11 * i1+ 50,50);
        label[i]->setGeometry(r1);
        label[i]->setImagePathName(i, "/home/srdzan/polyedit/VGEdit/res/delete.png");

    }
}

