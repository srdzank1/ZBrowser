#include "cmenuform.h"
#include "ui_cmenuform.h"

CMenuForm::CMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMenuForm)
{
    ui->setupUi(this);
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            label[i][j] = new SImageWidget(this);
            label[i][j]->resize(QSize(50, 50));
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
            int i1 = i +1;
            int j1 = j +1;
            QRect r1 = QRect(width/7 * i1, height/7 * j1 ,width/11 * i1+ 50, height/11 * j1 + 50);
            label[i][j]->setGeometry(r1);
            label[i][j]->setImagePathName(i, "/home/srdzan/polyedit/VGEdit/res/add.png");
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
