﻿#include "mainwindow.h"
#include "ui_mainwindow.h"


inline void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusHistoryEnabled = false;
    parser = 0;
    catIndx = 0;
    resizeCount = 0;
    admin = 0;
    editWebSites = 0;
    editSchedule = 0;
    checkProc = true;

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QRect rec = QApplication::desktop()->screenGeometry();
    height = rec.height();
    width = rec.width();

    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ "images/zac_zite_120.png"));

    createView();
    createViewInit();

    // start Init video
    t5 = new QTimer;
    connect(t5, SIGNAL(timeout()), this, SLOT(TimerFinish5()));
    t5->start(300);

    // start to show main Video
    t = new QTimer;
    connect(t, SIGNAL(timeout()), this, SLOT(TimerFinish()));
    t->start(15000);
    // start to load main Video
    t2 = new QTimer;
    connect(t2, SIGNAL(timeout()), this, SLOT(TimerFinish2()));
    t2->start(10000);

    // CreateLoader

    CreateLoader();

//    view->pageAction(QWebEnginePage::Forward);

    QString filePathHtml = ":/res/html/proc1.html";
    QFile file(filePathHtml);
    file.open(QIODevice::ReadOnly | QFile::Text);
    QTextStream in(&file);
    cont = in.readAll();

    QString filePathHtml2 = ":/res/html/proc2.html";
    QFile file2(filePathHtml2);
    file2.open(QIODevice::ReadOnly | QFile::Text);
    QTextStream in2(&file2);
    cont2 = in2.readAll();


    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    imgTmp.save(&buffer, "JPEG"); // writes the image in PNG format inside the buffer
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());


    QString bgImage = "";     //"data:image/jpg;base64,"+iconBase64;
    QString bgvideo = "https://player.vimeo.com/video/273431568"; //


    QString videoSound = "true";
    QString bgvideoSound;
    if (videoSound == "false"){
       bgvideoSound = "1";
    }else{
        bgvideoSound = "0";
    }

    bgvideo = bgvideo.trimmed();
    QString htmlCont= cont;
    htmlCont = htmlCont.replace("%url%",bgvideo);
    htmlCont = htmlCont.replace("%muted%",bgvideoSound);
    htmlCont = htmlCont.replace("%bkgimage%",bgImage);


    parser = new CParserXML(this);
    QString filePath = "://res/xml/menu.xml";
    parser->loadThemeXmlFile(filePath);



    QFuture<int> future = QtConcurrent::run(parser, &CParserXML::CreateCashImage);


    tgroup xmlData = parser->getParsedData();

    // CreateTopBarWidget
    CreateTopBarWidget();
    // create HeaderImageInfo
    CreateHeaderImageInfo(xmlData);
    // create horizontalMenu
    CreateHorizontalMenu(xmlData);
    // CreateCentralMenuScrollArea
    CreateCentralMenuScrollArea(xmlData);
    // CreateUpArrowWidget
    CreateUpArrowWidget();
    // CreateDownArrowWidget
    CreateDownArrowWidget();

    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
    scroll->setFocus();
    scroll->hide();


    // CreateBackArrowWidget
    CreateBackArrowWidget();
    // create CreateForwardWidget
    CreateForwardWidget();
    // create CreateHomeWidget
    CreateHomeWidget();
    // create CreateCloseOffWidget
    CreateCloseOffWidget();
    if (view->isHidden()){
        view->show();
    }
    // adminWidget
    CreateAdminWidget();
    // headerImageInfoCategory
    CreateHeaderImageInfoCategory(xmlData);
    scroll->setFocus();

}

void MainWindow::CreateLoader(){
    loader = new CLoaderWidget(this);
    loader->setGeometry(0,0, width, 6);
    loader->hide();
}

void MainWindow::CreateTopBarWidget(){
    topBarWidget = new CTopBarWidget(this);
    topBarWidget->setGeometry(0, 0, width, 60);
    topBarWidget->hide();
}


void MainWindow::CreateHeaderImageInfo(tgroup &xmlData){
    headerImageInfo = new CHeaderImageInfo(this);
    headerImageInfo->setGeometry(5,1, width, 49);
    headerImageInfo->setWidth(48);
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(0)->icon));
    headerImageInfo->setImage(0, imgTmp);
    headerImageInfo->setTitleIcon(xmlData.categories.at(0)->name);
    headerImageInfo->setHeight(48);
    headerImageInfo->hide();
}

void MainWindow::CreateHorizontalMenu(tgroup &xmlData){
    horizontalMenu = new QHorizontalMenu(this, xmlData);
    horizontalMenu->setGeometry(0,height-120, width, height);
    connect(horizontalMenu, SIGNAL(click(int)), this, SLOT(processClick(int)));
    horizontalMenu->hide();
}

void MainWindow::CreateCentralMenuScrollArea(tgroup &xmlData){
    int tempNum = width/200;
    int tempWidth = (tempNum-1)*200;
    int tempMarg = (width-tempWidth)/2;

    centralMenu = new CMenuForm(this, xmlData, tempWidth, height);
    connect(centralMenu, SIGNAL(clickForUrl(QString&, QString&, QImage &)), this, SLOT(ProcClickForUrl(QString&, QString&, QImage &)));
    centralMenu->setGeometry(QRect(tempMarg, 70, width-2*tempMarg, height-195));
    centralMenu->hide();

    scroll = new QScrollArea(this);
    scroll->setStyleSheet("background-color:transparent; border: none;");
    scroll->setStyleSheet("QScrollArea {background-color:transparent;border: none;}");
    scroll->setGeometry(QRect(tempMarg, 70, width-2*tempMarg, height-195));
    scroll->verticalScrollBar()->setRange(0, height);
    scroll->horizontalScrollBar()->setRange(0, 0);
    scroll->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scroll->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    scroll->setWidget(centralMenu);
    scroll->setFocus();
}

void MainWindow::CreateUpArrowWidget(){
    upArrowWidget = new CBaseWidget(this);
    connect(upArrowWidget, SIGNAL(buttonClick()), this, SLOT(ProcUpClick()));
    upArrowWidget->setGeometry(width - 68, 70, 48, 48);

    QImage upArrowTemp = QImage(":/res/image/arrowup_normal.png");
    QImage upArrowTemp_hover = QImage(":/res/image/arrowup_hover.png");
    QImage upArrowTemp_click = QImage(":/res/image/arrowup_click.png");
    upArrowWidget->setImage(0, upArrowTemp, upArrowTemp_hover,upArrowTemp_click);
    upArrowWidget->hide();
}

void MainWindow::CreateDownArrowWidget(){
    downArrowWidget = new CBaseWidget(this);
    connect(downArrowWidget, SIGNAL(buttonClick()), this, SLOT(ProcDownClick()));
    downArrowWidget->setGeometry(width - 68, height-175, 48, 48);

    QImage downArrowTemp = QImage(":/res/image/arrowdown_normal.png");
    QImage downArrowTemp_hover = QImage(":/res/image/arrowdown_hover.png");
    QImage downArrowTemp_click = QImage(":/res/image/arrowdown_click.png");
    downArrowWidget->setImage(0, downArrowTemp,downArrowTemp_hover,downArrowTemp_click);
    downArrowWidget->hide();

    scroll->hide();
    centralMenu->hide();
}

void MainWindow::CreateBackArrowWidget(){
    backWidget = new CBaseWidget(this);
    connect(backWidget, SIGNAL(buttonClick()), this, SLOT(ProcBackViewClick()));
    backWidget->setGeometry(width/2 - 50, 1, 48, 48);
    QImage backWidgetTemp = QImage(":/res/image/previous_normal.png");
    QImage backWidgetTemp_hover = QImage(":/res/image/previous_hover.png");
    QImage backWidgetTemp_click = QImage(":/res/image/previous_click.png");

    backWidget->setImage(0, backWidgetTemp, backWidgetTemp_hover,backWidgetTemp_click);
    backWidget->hide();
}

void MainWindow::CreateForwardWidget(){
    forwardWidget = new CBaseWidget(this);
    connect(forwardWidget, SIGNAL(buttonClick()), this, SLOT(ProcForwardViewClick()));
    forwardWidget->setGeometry(width/2 +50, 1, 48, 48);
    QImage forwardWidgetTemp = QImage(":/res/image/next_normal.png");
    QImage forwardWidgetTemp_hover = QImage(":/res/image/next_hover.png");
    QImage forwardWidgetTemp_click = QImage(":/res/image/next_click.png");
    forwardWidget->setImage(0, forwardWidgetTemp, forwardWidgetTemp_hover, forwardWidgetTemp_click);
    forwardWidget->hide();
}

void MainWindow::CreateHomeWidget(){
    homeWidget = new CBaseWidget(this);
    connect(homeWidget, SIGNAL(buttonClick()), this, SLOT(ProcHomeClick()));
    homeWidget->setGeometry(width/2 , 1, 48, 48);
    QImage homeWidgetTemp = QImage(":/res/image/home_normal.png");
    QImage homeWidgetTemp_hover = QImage(":/res/image/home_hover.png");
    QImage homeWidgetTemp_click = QImage(":/res/image/home_click.png");

    homeWidget->setImage(0, homeWidgetTemp, homeWidgetTemp_hover, homeWidgetTemp_click);
    homeWidget->hide();
}

void MainWindow::CreateCloseOffWidget(){
    closeOffWidget = new CBaseWidget(this);
    connect(closeOffWidget, SIGNAL(buttonClick()), this, SLOT(ProcCloseOffClick()));
    closeOffWidget->setGeometry(width - 115, 1, 48, 48);
    QImage closeOffWidgetTemp = QImage(":/res/image/close_normal.png");
    QImage closeOffWidgetTemp_hover = QImage(":/res/image/close_hover.png");
    QImage closeOffWidgetTemp_click = QImage(":/res/image/close_click.png");
    closeOffWidget->setImage(0, closeOffWidgetTemp, closeOffWidgetTemp_hover, closeOffWidgetTemp_click);
    closeOffWidget->hide();
}

void MainWindow::CreateAdminWidget(){
    adminWidget = new CBaseWidget(this);
    connect(adminWidget, SIGNAL(buttonClick()), this, SLOT(ProcAdminClick()));
    adminWidget->setGeometry(width - 60, 1, 50, 50);
    QImage adminWidgetTemp = QImage(":/res/image/admin_normal.png");
    QImage adminWidgetTemp_hover = QImage(":/res/image/admin_hover.png");
    QImage adminWidgetTemp_click = QImage(":/res/image/admin_click.png");
    adminWidget->setImage(0, adminWidgetTemp, adminWidgetTemp_hover, adminWidgetTemp_click);
    adminWidget->hide();
}

void MainWindow::CreateHeaderImageInfoCategory(tgroup &xmlData){
    headerImageInfoCategory = new CHeaderImageInfo(this);
    headerImageInfoCategory->setAnimate(true);
    headerImageInfoCategory->setGeometry(width -50 , 1, width, 49);
    headerImageInfoCategory->setWidth(48);
    QImage imgTmpCat = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(0)->icon));
    headerImageInfoCategory->setImage(0, imgTmpCat);
    headerImageInfoCategory->setTitleIcon("");
    headerImageInfoCategory->setHeight(48);
    connect(headerImageInfoCategory, SIGNAL(buttonClick()), this, SLOT(ProcCloseOffClick()));

    headerImageInfoCategory->hide();
}

void MainWindow::createView(){
    view = new QWebEngineView(this);
    view->setGeometry(0,0,width,height);
    view->hide();

    connect(view, SIGNAL(loadFinished(bool)),this, SLOT(procLoadUrlFinished(bool)));
    connect(view, SIGNAL(loadProgress(int )),this, SLOT(procLoadProgress(int)));
    connect(view, SIGNAL(urlChanged(const QUrl&)),this, SLOT(procLoadUrlChanged(const QUrl&)));
    connect(view->page(), SIGNAL(selectionChanged()),this, SLOT(procSelectionChanged()));

    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    view->history()->clear();

    connect(view->page(),
                &QWebEnginePage::fullScreenRequested,
                this,
                &MainWindow::fullScreenRequested);

    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

}

void MainWindow::createViewInit(){
    viewInit = new QWebEngineView(this);
    viewInit->setGeometry(0,0,width,height);
    QString pathTmp = ("file:///" +QDir::currentPath() +"/"+ "test1.html");

    viewInit->load(QUrl(pathTmp));
    viewInit->hide();
}


void MainWindow::TimerFinish(){
    viewInit->hide();
    connect(view, SIGNAL(loadStarted()),this, SLOT(procStartedUrlFinished()));

//    delete viewInit;
    adminWidget->show();
    horizontalMenu->setVisible(true);
    headerImageInfo->show();

    delete t;
}

void MainWindow::TimerFinish2(){

    processClickInit(0);
    delete t2;
}

void MainWindow::processClickInit(int i){
    statusHistoryEnabled = false;
    catIndx = i;

    if (catIndx == 0){
//        adminWidget->show();
    }else{
        adminWidget->hide();
    }

    if (catIndx != 0){
        if (admin != 0){
            delete admin;
            admin = 0;
        }
        if (editWebSites != 0){
            delete editWebSites;
            editWebSites = 0;
        }
        if (editSchedule != 0){
            delete editSchedule;
            editSchedule = 0;
        }
    }


    tgroup xmlData = parser->getParsedData();
    QImage imgTmpBkg = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->background));
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->icon));
    headerImageInfo->setImage(0, imgTmp);
    headerImageInfo->setTitleIcon(xmlData.categories.at(i)->name);


    centralMenu->setVisible(false);
    centralMenu->createMenuByCategory(i);
    centralMenu->setVisible(true);

    if(xmlData.categories.at(i)->websites.count()!=0){
        if (centralMenu->getRowMax()*200 > scroll->height()){
            downArrowWidget->show();
            upArrowWidget->show();
        }else{
            downArrowWidget->hide();
            upArrowWidget->hide();

        }
    }else{
        downArrowWidget->hide();
        upArrowWidget->hide();
    }


//    horizontalMenu->setVisible(true);
    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
    scroll->setFocus();
    scroll->show();

//    headerImageInfo->show();


    // background video
    QString bgvideo = xmlData.categories.at(i)->bgvideo;
    QString videoSound = xmlData.categories.at(i)->videosound;
    QString bgvideoSound;
    if (videoSound == "false"){
       bgvideoSound = "1";
    }else{
        bgvideoSound = "0";
    }

    bgvideo = bgvideo.trimmed();
    QString htmlCont= cont;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    imgTmpBkg.save(&buffer, "JPEG"); // writes the image in PNG format inside the buffer
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());

    QString bgImage = "data:image/jpg;base64,"+iconBase64;

    htmlCont = htmlCont.replace("%bkgimage%",bgImage);
    htmlCont = htmlCont.replace("%url%",bgvideo);
    htmlCont = htmlCont.replace("%muted%",bgvideoSound);
    view->setHtml(htmlCont);
    scroll->setFocus();
    repaint();

}




void MainWindow::TimerFinish5(){

   viewInit->show();
    delete t5;
}
void MainWindow::ProcUpClick(){
    scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value()-100);
}

void MainWindow::ProcDownClick(){
    scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value()+100);
}


void MainWindow::procStartedUrlFinished(){
    loader->show();
    loader->setValue(0);
}
void MainWindow::procLoadUrlFinished(bool s){
    loader->setValue(100);
    loader->hide();
//    if (view->isHidden()){
//        view->show();
//    }
}



void MainWindow::procLoadProgress(int s){
    loader->setValue(s);
}

    void MainWindow::ProcCloseOffClick(){

    statusHistoryEnabled = false;
    homeWidget->setVisible(false);
    closeOffWidget->setVisible(false);
    backWidget->setVisible(false);
    forwardWidget->setVisible(false);
    adminWidget->setVisible(false);
    view->setGeometry(QRect(0,0,width,height));
    view->history()->clear();
    topBarWidget->hide();
    headerImageInfoCategory->hide();
    if (catIndx == 0){
        adminWidget->show();
    }else{
        adminWidget->hide();
    }

//    emit horizontalMenu->click(catIndx);
    processClick(catIndx);
    checkProc = true;

}
void MainWindow::ProcAdminClick(){

    if (admin == 0){
        admin = new CAdminSettingsWidget(this);
        connect(admin, SIGNAL(clickForEditWebsitesMain()),this,SLOT(procEditWebsites()));
        connect(admin, SIGNAL(clickForScheduleMain()),this,SLOT(procEditSchedule()));
        admin->setGeometry(width - 402, 60, 385, 600);
        admin->show();
    }else{
        delete admin;
        admin = 0;
    }
    if (editWebSites != 0){
        delete editWebSites;
        editWebSites = 0;
    }
    if (editSchedule != 0){
        delete editSchedule;
        editSchedule = 0;
    }

 }

void MainWindow::procEditWebsites(){

    if (admin != 0){
        delete admin;
        admin = 0;
    }

    if (editWebSites == 0){
        tgroup data = parser->getParsedData();
        editWebSites = new CEditWebSites(data, this);
        editWebSites->setGeometry(60, 120, width - 120, height- 240);
        editWebSites->menuGlobalSettings();
        editWebSites->show();
    }else{
        delete editWebSites;
        editWebSites = 0;
    }

}

void MainWindow::procEditSchedule(){

    if (admin != 0){
        delete admin;
        admin = 0;
    }
    if (editSchedule == 0){
        tgroup data = parser->getParsedData();
        editSchedule = new CSchedule(data, this);
        editSchedule->setGeometry(60, 120, width - 120, height- 240);
        editSchedule->menuGlobalSettings();
        editSchedule->show();
    }else{
        delete editSchedule;
        editSchedule = 0;
    }

}

void MainWindow::ProcHomeClick(){
    QString htmlCont= cont2;
    htmlCont = htmlCont.replace("%url%",m_url);
    view->setHtml(htmlCont);

}

void MainWindow::procSelectionChanged(){
//    horizontalMenu->hide();
//    hiddenWidget->show();
}


void MainWindow::procLoadUrlChanged(const QUrl&){

    if (statusHistoryEnabled){
        horizontalMenu->hide();
//        hiddenWidget->show();
        int curIdx = view->history()->currentItemIndex();
        int numHI = view->history()->count();
        if (curIdx < numHI)
        {
            if(((numHI-curIdx) > 1)&&(curIdx >1)){
                backWidget->show();
                forwardWidget->show();
            }else if(((numHI-curIdx) <= 1)&&(curIdx >1)){
                backWidget->show();
                forwardWidget->hide();
            }else if(((numHI-curIdx) <= 1)&&(curIdx <=1)){
                backWidget->hide();
                forwardWidget->hide();
            }else if(((numHI-curIdx) > 1)&&(curIdx <=1)){
                backWidget->hide();
                forwardWidget->show();
            }

        }else{
            backWidget->hide();
            forwardWidget->hide();
        }
    }

}

void MainWindow::ProcBackViewClick(){
    view->page()->triggerAction(QWebEnginePage::Back);
}

void MainWindow::ProcForwardViewClick(){
    view->page()->triggerAction(QWebEnginePage::Forward);
}


void MainWindow::initVideo(){
}



void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if((event->key() == Qt::Key_L)&&(event->modifiers() == Qt::CTRL)){
        close();
    }
}

void MainWindow::fullScreenRequested(QWebEngineFullScreenRequest request)
{
    if (request.toggleOn()) {
        if (m_fullScreenWindow)
            return;
        request.accept();
        m_fullScreenWindow.reset(new FullScreenWindow(view));
    } else {
        if (!m_fullScreenWindow)
            return;
        request.accept();
        m_fullScreenWindow.reset();
    }
}

MainWindow::~MainWindow()
{
    delete view;
    delete viewInit;
    delete centralMenu;
    delete horizontalMenu;
    delete parser;
    delete viewInit;
    delete ui;
}

void MainWindow::processClick(int i){
    statusHistoryEnabled = false;
    if ((catIndx == i)&&checkProc){
        return;
    }
    catIndx = i;

    if (catIndx == 0){
        adminWidget->show();
    }else{
        adminWidget->hide();
    }

    if (catIndx != 0){
        if (admin != 0){
            delete admin;
            admin = 0;
        }
        if (editWebSites != 0){
            delete editWebSites;
            editWebSites = 0;
        }
        if (editSchedule != 0){
            delete editSchedule;
            editSchedule = 0;
        }
    }


    tgroup xmlData = parser->getParsedData();
    QImage imgTmpBkg = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->background));
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->icon));
    headerImageInfo->setImage(0, imgTmp);
    headerImageInfo->setTitleIcon(xmlData.categories.at(i)->name);


    centralMenu->setVisible(false);
    centralMenu->createMenuByCategory(i);
    centralMenu->setVisible(true);

    if(xmlData.categories.at(i)->websites.count()!=0){
        if (centralMenu->getRowMax()*200 > scroll->height()){
            downArrowWidget->show();
            upArrowWidget->show();
        }else{
            downArrowWidget->hide();
            upArrowWidget->hide();

        }
    }else{
        downArrowWidget->hide();
        upArrowWidget->hide();
    }


    horizontalMenu->setVisible(true);
    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
    scroll->setFocus();
    scroll->show();

    headerImageInfo->show();


    // background video
    QString bgvideo = xmlData.categories.at(i)->bgvideo;
    QString videoSound = xmlData.categories.at(i)->videosound;
    QString bgvideoSound;
    if (videoSound == "false"){
       bgvideoSound = "1";
    }else{
        bgvideoSound = "0";
    }

    bgvideo = bgvideo.trimmed();
    QString htmlCont= cont;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    imgTmpBkg.save(&buffer, "JPEG"); // writes the image in PNG format inside the buffer
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());

    QString bgImage = "data:image/jpg;base64,"+iconBase64;

    htmlCont = htmlCont.replace("%bkgimage%",bgImage);
    htmlCont = htmlCont.replace("%url%",bgvideo);
    htmlCont = htmlCont.replace("%muted%",bgvideoSound);
    view->setHtml(htmlCont);
    scroll->setFocus();
    repaint();

}


void MainWindow::ProcClickForUrl(QString &url, QString &title, QImage& imgTmp){

    adminWidget->hide();
    backWidget->setVisible(false);
    forwardWidget->setVisible(false);
    homeWidget->setVisible(false);
    closeOffWidget->setVisible(false);
    adminWidget->setVisible(false);

    statusHistoryEnabled = true;
    centralMenu->setVisible(false);

    scroll->setVisible(false);

    scroll->setFocus();

    downArrowWidget->setVisible(false);
    upArrowWidget->setVisible(false);

    headerImageInfo->setImage(0, imgTmp);

    headerImageInfo->setTitleIcon(title);

    headerImageInfo->setVisible(true);
    horizontalMenu->setVisible(false);
    homeWidget->setVisible(true);
    closeOffWidget->setVisible(false);
    adminWidget->setVisible(false);
    topBarWidget->show();
    tgroup xmlData = parser->getParsedData();

    QImage imgTmpCat = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(catIndx)->icon));
    headerImageInfoCategory->setImage(0, imgTmpCat);
    headerImageInfoCategory->show();

    view->setGeometry(QRect(0, 50, width, height-50));

    QString htmlCont= cont2;
    htmlCont = htmlCont.replace("%url%",url);
    view->hide();
    view->setHtml(htmlCont);
    view->show();
    m_url = url;
    view->history()->clear();
    checkProc = false;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (resizeCount == 0){
    view->setGeometry(0,0, width, height);

    horizontalMenu->setGeometry(0, height-130, width, height);
    horizontalMenu->UpdateD(QRect(0, 0, width, 130));
    int tempNum = width/200;
    int tempWidth = (tempNum-1)*200;
    int tempMarg = (width-tempWidth)/2;

    centralMenu->setGeometry(QRect(tempMarg, 70, width-2*tempMarg, height-195));
    centralMenu->UpdateD(QRect(tempMarg, 70, width-2*tempMarg, height-195));
    centralMenu->hide();
    QWidget::resizeEvent(event);
    resizeCount ++;
    }

}

void MainWindow::ProcShowHMenu(bool s){
    if (s){
        horizontalMenu->show();
//        hiddenWidget->hide();
    }
}

