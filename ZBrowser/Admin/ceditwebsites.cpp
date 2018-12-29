#include "ceditwebsites.h"

CEditWebSites::CEditWebSites(tgroup &data, QWidget *parent) : QWidget(parent)
{
//    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_group = data;
    categItems = 0;
    closeOffWidget = 0;
}

CEditWebSites::~CEditWebSites()
{

}

void CEditWebSites::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, geometry().width(), geometry().height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();

}

void CEditWebSites::menuGlobalSettings(){
    webEdit = new QLabel(this);
    webEdit->setGeometry(20,15, 300, 30);
    QFont cFont;
    cFont.setPointSize(16);
    cFont.setBold(true);
    webEdit->setFont(cFont);
    webEdit->setText(QStringLiteral("Edit websites"));

    categ = new CCategoryList(m_group, this);
    connect(categ, SIGNAL(clickForEdit(int&)), this, SLOT(procChangeCategory(int&)));
    connect(categ, SIGNAL(updateHorizontalMenu()),this, SLOT(procUpdateHorizontalMenu()));
    categ->setGeometry(QRect(20, 150, 300, geometry().height()-200));
    categ->createCategoryMenu(1);


    categScroll = new QScrollArea(this);
    categScroll->setStyleSheet("background-color:transparent; border: none;");
    categScroll->setStyleSheet("QScrollArea {background-color:transparent;border: none;}");
    categScroll->setGeometry(QRect(20, 150, 300, geometry().height()-200));
    categScroll->verticalScrollBar()->setRange(0, geometry().width());
    categScroll->horizontalScrollBar()->setRange(0, 0);
    categScroll->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    categScroll->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    categScroll->setWidget(categ);
    categScroll->setFocus();

    categItems = new CCategoryListItems(m_group, this);
    categItems->setGeometry(QRect(300, 50, geometry().width()-300, geometry().height()-100));
    categItems->createCategoryMenuItems(1);

    scroll = new QScrollArea(this);
    scroll->setStyleSheet("background-color:transparent; border: none;");
    scroll->setStyleSheet("QScrollArea {background-color:transparent;border: none;}");
    scroll->setGeometry(QRect(300, 50, geometry().width()-300, geometry().height()-100));
    scroll->verticalScrollBar()->setRange(0, geometry().width());
    scroll->horizontalScrollBar()->setRange(0, 0);
    scroll->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scroll->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    scroll->setWidget(categItems);
    scroll->setFocus();
    CreateCloseOffWidget();
}

void CEditWebSites::CreateCloseOffWidget(){
    closeOffWidget = new CBaseWidget(this);
    connect(closeOffWidget, SIGNAL(buttonClick()), this, SLOT(ProcCloseWebSites()));
    closeOffWidget->setGeometry(geometry().width() - 54, 6, 48, 48);
    QImage closeOffWidgetTemp = QImage(":/res/image/close_normal.png");
    QImage closeOffWidgetTemp_hover = QImage(":/res/image/close_hover.png");
    QImage closeOffWidgetTemp_click = QImage(":/res/image/close_click.png");
    closeOffWidget->setImage(0, closeOffWidgetTemp, closeOffWidgetTemp_hover, closeOffWidgetTemp_click);
    closeOffWidget->show();
}

void CEditWebSites::ProcCloseWebSites(){
    emit closeWebSites();
}


void CEditWebSites::procChangeCategory(int& i){
    emit webSitesChangeCategory(i);
}

void CEditWebSites::FuncChangeCategory(int& i, tfilterwebsite &efilter){
    categItems->hide();
    categItems->createCategoryMenuItems(i);
    categItems->setHideStatus(efilter);
    categItems->show();
    int stop = 0;
}


void CEditWebSites::setFilters(tfilterwebsite &efilter){
    categItems->setHideStatus(efilter);
}

void CEditWebSites::getFilters(tfilterwebsite &efilter){
    categItems->getHideStatus(efilter);
}

void CEditWebSites::setFiltersCategory(tfiltercategory &efilter){
    categ->setHideStatusCategory(efilter);
}

void CEditWebSites::getFiltersCategory(tfiltercategory &efilter){
    categ->getHideStatusCategory(efilter);
}

void CEditWebSites::procUpdateHorizontalMenu(){
    emit updateHorizMenu();
}
