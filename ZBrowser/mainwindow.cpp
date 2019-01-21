#include "mainwindow.h"
#include "ui_mainwindow.h"


inline void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

void MainWindow::ZackClock(){
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000);
}

void MainWindow::updateTimer(){

    if (mSettings.enableSchedule == true){

        QDateTime current = QDateTime::currentDateTime();
        int d = current.date().dayOfWeek();
        int h = current.time().hour();
        int m = current.time().minute() < 30 ? 0 : 30;

        QString key = QString::number(d-1, 10) + ":" + QString::number(h, 10)+ ":" + QString::number(m, 10);

        QMap<QString, QString> map;
        for (int i = 0; i < mFilteredSchedule.count(); i++){
            map.insert(mFilteredSchedule.at(i), mFilteredSchedule.at(i));
        }

        if (map[key] == key){
            statSleep = true;
        }else {
            statSleep = false;
        }

        if (statSleep != statSleepPrevious){
            statSleepPrevious = statSleep;
            if (statSleep){
                if(statusHistoryEnabled){
                    ProcCloseOffClick();
                }
                QString soundName = "snoring.wav";
                PlaySound(soundName);
                ProcClickForSleep();
            }else{
                QString soundName = "Woohoo.wav";
                PlaySound(soundName);
                catIndx = -1;
                processClick(0);
            }
        }
    }else{
        if (statSleepPrevious == true){
            statSleep = false;
            statSleepPrevious = false;

            QString soundName = "Woohoo.wav";
            PlaySound(soundName);
            catIndx = -1;
            processClick(0);
        }
    }
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
    passDialog = 0;
    registrationDialog = 0;
    verifyDialog = 0;
    editWebSites = 0;
    editSchedule = 0;
    msgDialog = 0;
    codeDialog = 0;
    checkProc = false;
    statSleep = false;
    statScreenSaver = false;
    statSleepPrevious = false;
    mSettings.KeyboardShortcut = "";
    mSettings.alwaysInFront = false;
    mSettings.enableRestriction = false;
    mSettings.enableSchedule = false;
    mSettings.exitKeyboardShortcut = false;
    mSettings.showCloseButton = false;

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QRect rec = QApplication::desktop()->screenGeometry();

    qApp->installEventFilter(this);

    height = rec.height();
    width = rec.width();
    ReadSettingData();
    ReadFilteredData();
    ReadFilteredDataCategory();
    ReadFilteredDataSchedule();
    readSettings();
    if (validateCode != "true"){
        mSettings.showCloseButton = true;
    }


    if (mSettings.alwaysInFront){
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    }else{
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    }

    timerSS = new QTimer(this);
    timerSS->setSingleShot(true);
    connect(timerSS, SIGNAL(timeout()), this, SLOT(updateTimerScreenShot()));
    verifyDialog = 0;
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (!checkProc){
        return false;
    }
    if ((event->type() == QEvent::MouseMove)||
        (event->type() == QEvent::KeyPress))
    {
        timerSS->stop();
        if(statScreenSaver){

            FadeinWidget(horizontalMenu);
            FadeinWidget(centralMenu);
            FadeinWidget(headerImageInfo);


            if(xmlData.categories.at(catIndx)->websites.count()!=0){
            if (centralMenu->getRowMax()*200 > scroll->height()){
                FadeinWidget(downArrowWidget);
                FadeinWidget(upArrowWidget);
            }else{
                FadeOutWidget(downArrowWidget);
                FadeOutWidget(upArrowWidget);
            }
        }else{
            FadeOutWidget(downArrowWidget);
            FadeOutWidget(upArrowWidget);
        }
            statScreenSaver = false;
        }
        timerSS->start(4000);
    }
     return false;
}


void MainWindow::FadeOutWidget(QWidget *w){
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    w->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(500);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
//    w->setVisible(false);
}


void MainWindow::FadeinWidget(QWidget *w){
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    w->setVisible(true);
    w->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(500);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}
// w is your widget

void MainWindow::updateTimerScreenShot(){
    FadeOutWidget(horizontalMenu);
    FadeOutWidget(centralMenu);
    FadeOutWidget(downArrowWidget);
    FadeOutWidget(upArrowWidget);
    statScreenSaver = true;
    if (checkProc){
        FadeOutWidget(headerImageInfo);
    }
}

void MainWindow::InitXMLGrabber(){
    autoTimer = new QTimer(this);
    autoTimer->setInterval(20000);
    autoTimer->setSingleShot(false);
    connect(autoTimer, SIGNAL(timeout()), this, SLOT(UpdateXMLFromWeb()));
    autoTimer->start();
}

void MainWindow::UpdateXMLFromWeb(){
    LoadXMLFileFromURLInit();
}

void MainWindow::CreateInitElement(){
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ "zac_zite_120.png"));

    CreateLoader();

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

    QFuture<int> future = QtConcurrent::run(parser, &CParserXML::CreateCashImage);


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

void MainWindow::LoadXMLFileFromURLInit(){
    QHelperC *cXml = new QHelperC();
    parser = new CParserXML(this);
    QString filePath = cXml->getWebXML();
    parser->SetXmlThemeXmlFile(filePath);
    xmlData = parser->getParsedData();
    QStringList foundedImages = GetAllImagesInFolder();
    for (int i = 0; i <xmlData.categories.count(); i++){
        QString bkgNameImage = xmlData.categories.at(i)->background;
        if (!ItemImageExist(foundedImages, bkgNameImage)) {
            QString urlImage = "http://zacbrowser.com/10/images/" + bkgNameImage;
            QByteArray data = cXml->getWebImage(urlImage);
            QString fileImagePath = QDir::toNativeSeparators(QDir::currentPath() +"/imagesAlfa/"+bkgNameImage);
            QFile file(fileImagePath);
            file.open(QIODevice::WriteOnly);
            file.write(data);
            file.close();
        }

        int stop = 0;
    }
    delete cXml;
}

void MainWindow::clearXMLData(){

    for (int i = 0; i < xmlData.categories.count(); i++ ){
        for (int j = 0; j < xmlData.categories.at(i)->websites.count(); i++ ){
            delete xmlData.categories.at(i)->websites.at(j);
        }
        delete xmlData.categories.at(i);
    }
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
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ xmlData.categories.at(0)->icon));
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
    connect(closeOffWidget, SIGNAL(buttonClick()), this, SLOT(ProcCloseApplication()));
    closeOffWidget->setGeometry(width - 60, 1, 48, 48);
    QImage closeOffWidgetTemp = QImage(":/res/image/close_normal.png");
    QImage closeOffWidgetTemp_hover = QImage(":/res/image/close_hover.png");
    QImage closeOffWidgetTemp_click = QImage(":/res/image/close_click.png");
    closeOffWidget->setImage(0, closeOffWidgetTemp, closeOffWidgetTemp_hover, closeOffWidgetTemp_click);
    closeOffWidget->hide();
}

void MainWindow::ProcShowCloseButton(bool stat){
    if (stat) {
        closeOffWidget->show();
    }else{
        closeOffWidget->hide();
    }
    closeOffWidget->repaint();
}

void MainWindow::CreateAdminWidget(){
    adminWidget = new CBaseWidget(this);
    connect(adminWidget, SIGNAL(buttonClick()), this, SLOT(ProcAdminClick()));
    adminWidget->setGeometry(width - 115, 1, 50, 50);
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
    QImage imgTmpCat = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ xmlData.categories.at(0)->icon));
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
    connect(viewInit, SIGNAL(loadFinished(bool)),this, SLOT(procLoadInitVideoFinished(bool)));

    viewInit->setGeometry(0,0,width,height);
    QString pathTmp = ("file:///" +QDir::currentPath() +"/"+ "intro.html");

    viewInit->load(QUrl(pathTmp));
    viewInit->hide();
}
void MainWindow::TimerFinish(){
    viewInit->hide();
    connect(view, SIGNAL(loadStarted()),this, SLOT(procStartedUrlFinished()));

//    delete viewInit;
    ProcShowCloseButton(mSettings.showCloseButton);
    adminWidget->show();
    procupdateHorizMenu();
    horizontalMenu->setVisible(true);
    headerImageInfo->show();
    ZackClock();
    delete t;
    checkProc = true;

//    ProcPasswordDialog();
//    ProcRegVerifyDialog();
//    ProcRegistrationDialog();

}

void MainWindow::procLoadInitVideoFinished(bool s){
    // start Init video
    t5 = new QTimer;
    connect(t5, SIGNAL(timeout()), this, SLOT(TimerFinish5()));
    t5->start(0);

    // start to show main Video
    t = new QTimer;
    connect(t, SIGNAL(timeout()), this, SLOT(TimerFinish()));
    t->start(13900);
    // start to load main Video
    t2 = new QTimer;
    connect(t2, SIGNAL(timeout()), this, SLOT(TimerFinish2()));
    t2->start(0);

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


    QImage imgTmpBkg = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ xmlData.categories.at(i)->background));
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ xmlData.categories.at(i)->icon));
    headerImageInfo->setImage(0, imgTmp);
    headerImageInfo->setTitleIcon(xmlData.categories.at(i)->name);


    centralMenu->setVisible(false);
    centralMenu->createMenuByCategory(i, mFilteredWeb, mSettings);
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
    QString bgvideo = ParseTransform(xmlData.categories.at(i)->bgvideo);
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
//    loader->show();
//    loader->setValue(0);
}
void MainWindow::procLoadUrlFinished(bool s){
//    loader->setValue(100);
//    loader->hide();
}
void MainWindow::procLoadProgress(int s){
    loader->setValue(s);
}
void MainWindow::ProcCloseOffClick(){

    statusHistoryEnabled = false;
    homeWidget->setVisible(false);
    closeOffWidget->setVisible(true);
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

    processClick(catIndx);
    checkProc = true;

}
void MainWindow::ProcCloseApplication(){
    close();
}

void MainWindow::ProcCloseAdminMenu(){
    admin->getSettings(mSettings);
    delete admin;
    admin = 0;
}

void MainWindow::procCloseWebSites(){
    if(admin != 0){
        admin->getSettings(mSettings);
        delete admin;
        admin = 0;
    }
    if (editWebSites != 0){
        editWebSites->getFilters(mFilteredWeb);
        editWebSites->getFiltersCategory(mFilteredCategory);
        delete editWebSites;
        editWebSites = 0;
    }
    if (editSchedule != 0){
        editSchedule->getFilterSchedule(mFilteredSchedule);
        delete editSchedule;
        editSchedule = 0;
    }

    if (admin == 0){
        admin = new CAdminSettingsWidget(this);
        connect(admin, SIGNAL(clickForEditWebsitesMain()),this,SLOT(procEditWebsites()));
        connect(admin, SIGNAL(clickForScheduleMain()),this,SLOT(procEditSchedule()));
        connect(admin, SIGNAL(clickForShowCloseButton(bool)), this, SLOT(ProcShowCloseButton(bool)));
        connect(admin, SIGNAL(clickForCloseApplication()), this, SLOT(ProcCloseApplication()));
        connect(admin, SIGNAL(clickForCloseMenu()), this, SLOT(ProcCloseAdminMenu()));
        connect(admin, SIGNAL(changeEnableRestriction()), this, SLOT(ProcChangeEnableRestriction()));
        connect(admin, SIGNAL(changeEnableSchedule()), this, SLOT(ProcChangeEnableSchedule()));


        admin->setGeometry(width - 402, 60, 385, 600);
        admin->setSettings(mSettings);

        admin->show();
    }else{
        admin->getSettings(mSettings);
        delete admin;
        admin = 0;
    }
    if (editWebSites != 0){
        editWebSites->getFilters(mFilteredWeb);
        editWebSites->getFiltersCategory(mFilteredCategory);
        delete editWebSites;
        editWebSites = 0;
    }
    if (editSchedule != 0){
        editSchedule->getFilterSchedule(mFilteredSchedule);
        delete editSchedule;
        editSchedule = 0;
    }

}

//---------------------------------------------------------------------------------------------------

void MainWindow::ProcPasswordDialog(){
    if (passDialog == 0){
        passDialog = new CPasswordDialog(this);
        connect(passDialog, SIGNAL(clickOK()),this,SLOT(procOkPasswordDialog()));
        connect(passDialog, SIGNAL(clickCancel()),this,SLOT(procCancelPasswordDialog()));
        connect(passDialog, SIGNAL(clickRecovery()),this,SLOT(procRecoveryPasswordDialog()));

        passDialog->setGeometry(width /2 - 200, height / 2 - 100, 400, 200);
        passDialog->dialogSettings();
        passDialog->show();
    }
}
void MainWindow::procOkPasswordDialog(){

    QString tCode = passDialog->userEdit->text();
    QByteArray bCode = tCode.toUtf8();


    if(Hash(bCode) == codeHash){
        delete passDialog;
        passDialog = 0;
        if (admin == 0){
            admin = new CAdminSettingsWidget(this);
            connect(admin, SIGNAL(clickForEditWebsitesMain()),this,SLOT(procEditWebsites()));
            connect(admin, SIGNAL(clickForScheduleMain()),this,SLOT(procEditSchedule()));
            connect(admin, SIGNAL(clickForShowCloseButton(bool)), this, SLOT(ProcShowCloseButton(bool)));
            connect(admin, SIGNAL(clickForCloseApplication()), this, SLOT(ProcCloseApplication()));
            connect(admin, SIGNAL(clickForCloseMenu()), this, SLOT(ProcCloseAdminMenu()));
            connect(admin, SIGNAL(changeEnableRestriction()), this, SLOT(ProcChangeEnableRestriction()));
            connect(admin, SIGNAL(changeEnableSchedule()), this, SLOT(ProcChangeEnableSchedule()));
            connect(admin, SIGNAL(changealwaysInFront(bool)), this, SLOT(ProcAlwaysInFront(bool)));


            admin->setGeometry(width - 402, 60, 385, 600);
            admin->setSettings(mSettings);

            admin->show();
        }else{
            admin->getSettings(mSettings);
            delete admin;
            admin = 0;
        }
        if (editWebSites != 0){
            editWebSites->getFilters(mFilteredWeb);
            editWebSites->getFiltersCategory(mFilteredCategory);
            delete editWebSites;
            editWebSites = 0;
        }
        if (editSchedule != 0){
            editSchedule->getFilterSchedule(mFilteredSchedule);
            delete editSchedule;
            editSchedule = 0;
        }
    }else{
        delete passDialog;
        passDialog = 0;
    }
}
void MainWindow::procCancelPasswordDialog(){
    delete passDialog;
    passDialog = 0;
}
void MainWindow::procRecoveryPasswordDialog(){
    sendEmail(emailReg);
    // to do add message box
    procMsgDialog("Info", "Check your email! "+ convertEmailToHiden(emailReg));
}

//---------------------------------------------------------------------------------------------------
void MainWindow::ProcRegVerifyDialog(){
    if (verifyDialog == 0){
        verifyDialog = new CRegistrationVerifyDialog(this);
        QString tempEmail = convertEmailToHiden(emailReg);
        verifyDialog->setEmailText(tempEmail);
        connect(verifyDialog, SIGNAL(clickOK()),this,SLOT(procOkVerifyDialog()));
        connect(verifyDialog, SIGNAL(clickCancel()),this,SLOT(procCancelVerifyDialog()));
        connect(verifyDialog, SIGNAL(clickNewCode()),this,SLOT(procNewCodeVerifyDialog()));
        connect(verifyDialog, SIGNAL(clickNewEmail()),this,SLOT(procNewEmailVerifyDialog()));

        verifyDialog->setGeometry(width /2 - 200, height / 2 - 100, 400, 200);
        verifyDialog->dialogSettings();
        verifyDialog->show();
    }
}
void MainWindow::procOkVerifyDialog(){
    QString tempCode;
    tempCode = verifyDialog->userEdit->text();
    if (codeHash == Hash(tempCode.toUtf8())) {
        validateCode = "true";
        // to do add message box
        procMsgDialog("Info", "Code is match!");
        delete verifyDialog;
        verifyDialog = 0;

    }else{
        validateCode = "false";
        // to do add message box
        procMsgDialog("Warning", "Code is not match!");

    }
}
void MainWindow::procCancelVerifyDialog(){
    delete verifyDialog;
    verifyDialog = 0;
}
void MainWindow::procNewCodeVerifyDialog(){
    sendEmail(emailReg);
    procMsgDialog("Warning", "Check your email for code! "+convertEmailToHiden(emailReg));
}

void MainWindow::procNewEmailVerifyDialog(){
    delete verifyDialog;
    verifyDialog = 0;
    ProcRegistrationDialog();
}

//-------------------------------------------------------------------------------------------------------

void MainWindow::ProcRegistrationDialog(){
    if (registrationDialog == 0){
        registrationDialog = new CRegistrationDialog(this);
        connect(registrationDialog, SIGNAL(clickOK()),this,SLOT(procOkRegistrationDialog()));
        connect(registrationDialog, SIGNAL(clickCancel()),this,SLOT(procCancelRegistrationDialog()));

        registrationDialog->setGeometry(width /2 - 200, height / 2 - 100, 450, 250);
        registrationDialog->dialogSettings();
        registrationDialog->show();
    }
}
void MainWindow::procOkRegistrationDialog(){
    QString tempEmail = registrationDialog->userEdit->text();
    if (validaEmail(tempEmail)){
        emailReg = tempEmail;
        sendEmail(emailReg);
        validateCode = "false";
        procCancelRegDialog();
        ProcRegVerifyDialog();
    }else{
        procMsgDialog("Warning", "Email is not valid!");
    }
}
void MainWindow::procCancelRegistrationDialog(){
    procCancelRegDialog();
}

//--------------------------------------------------------------------------------------------------------

void MainWindow::ProcAdminClick(){
    if(admin != 0){
        admin->getSettings(mSettings);
        delete admin;
        admin = 0;
    }
    if (editWebSites != 0){
        editWebSites->getFilters(mFilteredWeb);
        editWebSites->getFiltersCategory(mFilteredCategory);
        delete editWebSites;
        editWebSites = 0;
    }
    if (editSchedule != 0){
        editSchedule->getFilterSchedule(mFilteredSchedule);
        delete editSchedule;
        editSchedule = 0;
    }
    validateCode = "false";
    if (validateCode != "true"){
        ProcRegistrationDialog();
    }else{
        ProcPasswordDialog();
    }
}


void MainWindow::ProcAlwaysInFront(bool stat){
    if (stat) {
        mSettings.alwaysInFront = true;
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    }else{
        mSettings.alwaysInFront = false;
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    }
}

void MainWindow::ProcChangeEnableRestriction(){
    if (!statSleep){
        admin->getSettings(mSettings);
        procupdateHorizMenu();
    }
}

void MainWindow::ProcChangeEnableSchedule(){
    admin->getSettings(mSettings);
//    updateTimer();
}

void MainWindow::procEditWebsites(){

    if (admin != 0){
        delete admin;
        admin = 0;
    }

    if (editWebSites == 0){
        tgroup data = parser->getParsedData();

        editWebSites = new CEditWebSites(data, this);
        connect(editWebSites, SIGNAL(webSitesChangeCategory(int&)), this, SLOT(procWebSitesChangeCategory(int&)));
        connect(editWebSites, SIGNAL(closeWebSites()), this, SLOT(procCloseWebSites()));
        connect(editWebSites, SIGNAL(updateHorizMenu()),this, SLOT(procupdateHorizMenu()));
        editWebSites->setGeometry(60, 120, width - 120, height- 240);
        editWebSites->menuGlobalSettings();
        editWebSites->setFilters(mFilteredWeb);
        editWebSites->setFiltersCategory(mFilteredCategory);

        editWebSites->show();
    }else{
        editWebSites->getFilters(mFilteredWeb);
        editWebSites->getFiltersCategory(mFilteredCategory);
        delete editWebSites;
        editWebSites = 0;
    }

}


void MainWindow::procupdateHorizMenu(){
    xmlData = parser->getParsedData();

    if (editWebSites){
        editWebSites->getFilters(mFilteredWeb);
        editWebSites->getFiltersCategory(mFilteredCategory);
    }

    tgroup xmlDataTemp;
    QList<tcategory*>::iterator it2;
    if(mSettings.enableRestriction == true){
        QMap<QString, QString> map;
        for(int ia = 0; ia < mFilteredCategory.count(); ia++){
            map.insert(mFilteredCategory.at(ia), mFilteredCategory.at(ia));
        }

        for (it2 = xmlData.categories.begin(); it2  != xmlData.categories.end(); it2++){
            tcategory* item = (*it2);
            if (!map.contains(item->name)){
                xmlDataTemp.categories.append(item);
            }
        }
        xmlData = xmlDataTemp;
    }


    if(horizontalMenu){
        delete horizontalMenu;
        horizontalMenu = 0;
    }
    if (!horizontalMenu){
        CreateHorizontalMenu(xmlData);
        horizontalMenu->setGeometry(0, height-130, width, height);
        horizontalMenu->UpdateD(QRect(0, 0, width, 130));
        if (!statSleep){
            horizontalMenu->show();
            update();
        }
    }
}

void MainWindow::procWebSitesChangeCategory(int&i){
    editWebSites->getFilters(mFilteredWeb);
    editWebSites->FuncChangeCategory(i, mFilteredWeb);

    int stop = 0;
}

void MainWindow::procEditSchedule(){

    if (admin != 0){
        delete admin;
        admin = 0;
    }
    if (editSchedule == 0){
        tgroup data = xmlData;

        editSchedule = new CSchedule(data, this);
        connect(editSchedule, SIGNAL(closeWebSites()), this, SLOT(procCloseWebSites()));
        editSchedule->setGeometry(60, 120, width - 120, height- 240);
        editSchedule->menuGlobalSettings();
        editSchedule->setFilterSchedule(mFilteredSchedule);
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
    createView();
    createViewInit();

}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if (!mSettings.exitKeyboardShortcut){
        return;
    }
    int keyS = 0;
    keyS =QChar(mSettings.KeyboardShortcut[0]).toLatin1();
    if((event->key() == keyS )&&(event->modifiers() == Qt::CTRL)){
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
    SaveSettingData();
    SaveFilteredData();
    SaveFilteredDataCategory();
    SaveFilteredDataSchedule();
    writeSettings();
    delete view;
    delete viewInit;
    delete centralMenu;
    delete horizontalMenu;
    delete parser;
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
            admin->getSettings(mSettings);
            delete admin;
            admin = 0;
        }
        if (editWebSites != 0){
            editWebSites->getFilters(mFilteredWeb);
            editWebSites->getFiltersCategory(mFilteredCategory);
            delete editWebSites;
            editWebSites = 0;
        }
        if (editSchedule != 0){
            editSchedule->getFilterSchedule(mFilteredSchedule);
            delete editSchedule;
            editSchedule = 0;
        }

        if (passDialog != 0){
            delete passDialog;
            passDialog = 0;
        }
        if (registrationDialog != 0){
            delete registrationDialog;
            registrationDialog = 0;
        }
        if (msgDialog != 0){
            delete msgDialog;
            msgDialog = 0;
        }
        if (codeDialog != 0){
            delete codeDialog;
            codeDialog = 0;
        }

    }


    QImage imgTmpBkg = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ xmlData.categories.at(i)->background));
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ xmlData.categories.at(i)->icon));
    headerImageInfo->setImage(0, imgTmp);
    headerImageInfo->setTitleIcon(xmlData.categories.at(i)->name);

    centralMenu->setVisible(false);
    centralMenu->setXMLData(xmlData);
    centralMenu->createMenuByCategory(i, mFilteredWeb, mSettings);
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
    headerImageInfo->repaint();


    // background video
    QString bgvideo = ParseTransform(xmlData.categories.at(i)->bgvideo);
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


void MainWindow::ProcClickForSleep(){
    QString url= "https://vimeo.com/248425744/adbf4e7413";
    statusHistoryEnabled = false;

    centralMenu->setVisible(false);
    horizontalMenu->setVisible(false);

    QString bgvideo = ParseTransform(url);
    QString videoSound = "true";
    QString bgvideoSound;
    if (videoSound == "false"){
       bgvideoSound = "1";
    }else{
        bgvideoSound = "0";
    }

    bgvideo = bgvideo.trimmed();
    QString htmlCont= cont;

    QString bgImage = "";

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
    headerImageInfo->update();
    horizontalMenu->setVisible(false);
    homeWidget->setVisible(true);
    closeOffWidget->setVisible(false);
    adminWidget->setVisible(false);
    topBarWidget->show();

    QImage imgTmpCat = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ xmlData.categories.at(catIndx)->icon));
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
QStringList MainWindow::GetAllImagesInFolder(){
   QDir directory(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR));
   QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);
    return images;
}
bool MainWindow::ItemImageExist(QStringList &images, QString & item){
   bool status;
   status = false;
    QStringList::iterator it;
   for (it = images.begin(); it != images.end(); it++){
       if (*it == item){
           status = true;
           break;
       }
   }
   return status;
}
QString MainWindow::ParseTransform(QString url){
    if (url.contains("vimeo", Qt::CaseInsensitive)){
        url.replace(QString("vimeo.com"), QString("player.vimeo.com/video"));
    }
    if (url.contains("youtube", Qt::CaseInsensitive)){
        url.replace(QString("www.youtube.com/watch?v="), QString("www.youtube.com/embed/"));
    }
    return url;
}

void MainWindow::SaveSettingData(){
//    QString fileImagePath = QDir::toNativeSeparators(QDir::currentPath() +"/settings.dat");
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/settings.dat");
    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << mSettings.KeyboardShortcut;
    out << mSettings.alwaysInFront;
    out << mSettings.enableRestriction;
    out << mSettings.enableSchedule;
    out << mSettings.exitKeyboardShortcut;
    out << mSettings.showCloseButton;
}

void MainWindow::ReadSettingData(){
//    QString fileImagePath = QDir::toNativeSeparators(QDir::currentPath() +"/settings.dat");
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/settings.dat");

    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);   // we will serialize the data into the file
    in >> mSettings.KeyboardShortcut;
    in >> mSettings.alwaysInFront;
    in >> mSettings.enableRestriction;
    in >> mSettings.enableSchedule;
    in >> mSettings.exitKeyboardShortcut;
    in >> mSettings.showCloseButton;
}

void MainWindow::SaveFilteredData(){
//    QString fileImagePath = QDir::toNativeSeparators(QDir::currentPath() +"/filtered.dat");
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/filtered.dat");

    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << mFilteredWeb.count(); // size of map
    tfilterwebsite::iterator it;

    for (it = mFilteredWeb.begin(); it != mFilteredWeb.end(); it++){
        out << (*it);
    }
}

void MainWindow::ReadFilteredData(){
//    QString fileImagePath = QDir::toNativeSeparators(QDir::currentPath() +"/filtered.dat");
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/filtered.dat");

    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);   // we will serialize the data into the file
    int count;
    in >> count;
    mFilteredWeb.clear();
    for(int i = 0; i < count; i++){
        QString item;
        in >> item;
        mFilteredWeb.append(item);
    }
}

void MainWindow::SaveFilteredDataCategory(){
//    QString fileImagePath = QDir::toNativeSeparators(QDir::currentPath() +"/filtered.dat");
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/category.dat");

    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << mFilteredCategory.count(); // size of map
    tfilterwebsite::iterator it;

    for (it = mFilteredCategory.begin(); it != mFilteredCategory.end(); it++){
        out << (*it);
    }
}

void MainWindow::ReadFilteredDataCategory(){
//    QString fileImagePath = QDir::toNativeSeparators(QDir::currentPath() +"/filtered.dat");
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/category.dat");

    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);   // we will serialize the data into the file
    int count;
    in >> count;
    mFilteredCategory.clear();
    for(int i = 0; i < count; i++){
        QString item;
        in >> item;
        mFilteredCategory.append(item);
    }
}

void MainWindow::SaveFilteredDataSchedule(){
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/schedule.dat");

    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << mFilteredSchedule.count(); // size of map
    tfilterschedule::iterator it;

    for (it = mFilteredSchedule.begin(); it != mFilteredSchedule.end(); it++){
        out << (*it);
    }
}

void MainWindow::ReadFilteredDataSchedule(){
    QString fileImagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation) +"/schedule.dat");

    QFile file(fileImagePath);
    file.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);   // we will serialize the data into the file
    int count;
    in >> count;
    mFilteredSchedule.clear();
    for(int i = 0; i < count; i++){
        QString item;
        in >> item;
        mFilteredSchedule.append(item);
    }
}


void MainWindow::PlaySound(QString &soundName){
    QString pathFile = QDir::toNativeSeparators(QDir::currentPath() +"/sounds/"+soundName);
    QSound::play(pathFile);
}


void MainWindow::writeSettings()
{
    QSettings settings("ZacBrowser", "ZB");

    settings.beginGroup("MainWindow");
    settings.setValue("email", emailReg);
    settings.setValue("code", codeHash);
    settings.setValue("validateCode", validateCode);

    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("ZacBrowser", "ZB");

    settings.beginGroup("MainWindow");
    emailReg = settings.value("email").toString();
    codeHash = settings.value("code").toString();
    validateCode = settings.value("validateCode").toString();

    settings.endGroup();
}

QString MainWindow::Hash(const QByteArray &s){
    QString hashString = QString(QCryptographicHash::hash((s),QCryptographicHash::Md5).toHex());
    return hashString;
}

void MainWindow::sendEmail(QString &emailAdd)
{
    // Create the email object
    Email email = createEmail(emailAdd);

    // Create the SMTPClient
    client_ = new SMTPClient("mail.zacbrowser.com", 465);

    // Try to send the email
    client_->sendEmail(email);
}

Email MainWindow::createEmail(QString &emailAddr)
{
    // Create the credentials EmailAddress
    EmailAddress credentials("software@zacbrowser.com","vS[e!g}p7MBe");

    // Create the from EmailAddress
    EmailAddress from("software@zacbrowser.com");

    // Create the to EmailAddress
    EmailAddress to(emailAddr);
    QString tempCode = randString(2)+randNumString(2);
    codeHash = Hash(tempCode.toUtf8());
    // Create the email
    Email email(credentials,
                from,
                to,
                "Zac Browser", // subject
                "Thank you for choosing Zac Browser. \n"
                "Please use this code to unlock the admin section: " + tempCode + "\n"
                "If you require any further assistance, please feel free \n"
                "to visit our support forms: https://zacbrowser.com/forum \n"
                "Kindest regards,\n"
                "Zac Browser Team"
                );
    return email;
}

QString MainWindow::randString(int len)
{
    QString str;
    str.resize(len);
    for (int s = 0; s < len ; ++s)
        str[s] = QChar('A' + char(qrand() % ('Z' - 'A')));
    return str;
}

QString MainWindow::randNumString(int len)
{
    QString str;
    str.resize(len);
    for (int s = 0; s < len ; ++s)
        str[s] = QChar('0' + char(qrand() % ('9' - '0')));
    return str;
}



void MainWindow::ProcValidateCodeDialog(){
    if (codeDialog == 0){
        codeDialog = new CCodeDialog(this);
        connect(codeDialog, SIGNAL(clickOK()),this,SLOT(procOkValidateCodeDialog()));
        connect(codeDialog, SIGNAL(clickCancel()),this,SLOT(procCancelValidateCodeDialog()));
//        connect(codeDialog, SIGNAL(clickAskCode()),this,SLOT(procAskValidateCodeDialog()));

        codeDialog->setGeometry(width /2 - 200, height / 2 - 100, 450, 250);
        codeDialog->dialogSettings();
        codeDialog->show();
    }
}

void MainWindow::procOkValidateCodeDialog(){
    // if condition is valid
    if (Hash(codeDialog->userEdit->text().toUtf8()) == codeHash){
        validateCode = "true";
        procCancelValidateCodeDialog();
        ProcPasswordDialog();
    }else{
        procMsgDialog("Warning", "Code is not match!");
    }

}
void MainWindow::procCancelValidateCodeDialog(){
    delete codeDialog;
    codeDialog = 0;
}
//void MainWindow::procAskValidateCodeDialog(){
//    // add code here
//    ProcRegistrationDialog();
//}


void MainWindow::procMsgDialog(const QString& title, const QString& info){
    if (msgDialog == 0){
        msgDialog = new CMessageDialog();
        msgDialog->setParent(this);
        connect(msgDialog, SIGNAL(clickOK()),this,SLOT(procOkMsgDialog()));
        msgDialog->setGeometry(width /2 - 200, height / 2 - 100, 450, 250);
        msgDialog->dialogSettings(title, info);
        msgDialog->show();
    }
}

void MainWindow::procOkMsgDialog(){
    delete msgDialog;
    msgDialog = 0;
}

void MainWindow::procCancelRegDialog(){
    delete registrationDialog;
    registrationDialog = 0;
}

bool MainWindow::validaEmail(QString email)
{
    bool retorno = true;
    qDebug() << email;
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
    if(!regex.match(email).hasMatch())
    {
        retorno = false;
    }
    return retorno;
}

QString MainWindow::convertEmailToHiden(QString email){
    QStringList tempList;
    tempList = email.split("@");
    QString firstPart = tempList.at(0);
    QString lastPart = tempList.at(1);
    firstPart = firstPart.replace(0, 1, "*");
    firstPart = firstPart.replace(firstPart.length()-1, 1, "*");

    lastPart = lastPart.replace(0, 1, "*");
    lastPart = lastPart.replace(lastPart.length()-1, 1, "*");
    email = firstPart+"@"+lastPart;
    return email;
}

