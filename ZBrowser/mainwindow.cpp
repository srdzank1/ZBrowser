#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusHistoryEnabled = false;
    parser = 0;
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QRect rec = QApplication::desktop()->screenGeometry();
    height = rec.height();
    width = rec.width();


    backgroundImage = new CCentralBackgroundImage(this);
    backgroundImage->setGeometry(0,0, width, height);
    backgroundImage->setWidth(width);
    backgroundImage->show();


    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ "images/0138dd49a38e8e64eb2a4738dba6dc4f_6478f.jpg"));
    backgroundImage->setImage(0,imgTmp);
    backgroundImage->setHeight(height);

    view = new QWebEngineView(this);
    view->setGeometry(0,0,width,height);
    connect(view, SIGNAL(loadFinished(bool)),this, SLOT(procLoadUrlFinished(bool)));
    connect(view, SIGNAL(urlChanged(const QUrl&)),this, SLOT(procLoadUrlChanged(const QUrl&)));
    connect(view->page(), SIGNAL(selectionChanged()),this, SLOT(procSelectionChanged()));



    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    connect(view->page(),
                &QWebEnginePage::fullScreenRequested,
                this,
                &MainWindow::fullScreenRequested);


    view->pageAction(QWebEnginePage::Forward);
    QString filePathHtml = ":/res/html/proc1.html";
    QFile file(filePathHtml);
    file.open(QIODevice::ReadOnly | QFile::Text);
    QTextStream in(&file);
    cont = in.readAll();


    QString bgvideo = "https://player.vimeo.com/video/182513271";
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

    view->setHtml(htmlCont);
    view->show();


    parser = new CParserXML(this);
    QString filePath = "://res/xml/menu.xml";
    parser->loadThemeXmlFile(filePath);



    QFuture<int> future = QtConcurrent::run(parser, &CParserXML::CreateCashImage);

    tgroup xmlData = parser->getParsedData();

    headerImageInfo = new CHeaderImageInfo(this);
    headerImageInfo->setGeometry(5,5, width, 60);
    headerImageInfo->setWidth(50);
    imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(0)->icon));
    headerImageInfo->setImage(0, imgTmp);
    headerImageInfo->setTitleIcon(xmlData.categories.at(0)->name);
    headerImageInfo->setHeight(50);
    headerImageInfo->show();



    horizontalMenu = new QHorizontalMenu(this, xmlData);
    horizontalMenu->setGeometry(0,height-120, width, height);
    connect(horizontalMenu, SIGNAL(click(int)), this, SLOT(processClick(int)));

    int tempNum = width/200;
    int tempWidth = (tempNum-1)*200;
    int tempMarg = (width-tempWidth)/2;

    centralMenu = new CMenuForm(this, xmlData, tempWidth, height);
    connect(centralMenu, SIGNAL(clickForUrl(QString&, QString&)), this, SLOT(ProcClickForUrl(QString&, QString&)));
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

    upArrowWidget = new CBaseWidget(this);
    connect(upArrowWidget, SIGNAL(buttonClick()), this, SLOT(ProcUpClick()));
    upArrowWidget->setGeometry(width - 68, 70, 50, 50);
    QImage upArrowTemp = QImage(":/res/image/if_f-top_256_282460.png");

    upArrowWidget->setImage(0, upArrowTemp);
    upArrowWidget->hide();

    downArrowWidget = new CBaseWidget(this);
    connect(downArrowWidget, SIGNAL(buttonClick()), this, SLOT(ProcDownClick()));
    downArrowWidget->setGeometry(width - 68, height-175, 50, 50);
//    QImage downArrowTemp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ "images/bottom.png"));
    QImage downArrowTemp = QImage(":/res/image/if_f-bottom_256_282477.png");

    downArrowWidget->setImage(0, downArrowTemp);
    downArrowWidget->hide();

    scroll->hide();
    backgroundImage->hide();
    centralMenu->hide();

    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
    scroll->hide();
    scroll->setFocus();
    backgroundImage->show();



    backWidget = new CBaseWidget(this);
    connect(backWidget, SIGNAL(buttonClick()), this, SLOT(ProcBackViewClick()));
    backWidget->setGeometry(width - 225, 5, 50, 50);
    QImage backWidgetTemp = QImage(":/res/image/if_f-left_256_282467.png");
    backWidget->setImage(0, backWidgetTemp);
    backWidget->hide();


    forwardWidget = new CBaseWidget(this);
    connect(forwardWidget, SIGNAL(buttonClick()), this, SLOT(ProcForwardViewClick()));
    forwardWidget->setGeometry(width - 170, 5, 50, 50);
    QImage forwardWidgetTemp = QImage(":/res/image/if_f-right_256_282463.png");
    forwardWidget->setImage(0, forwardWidgetTemp);
    forwardWidget->hide();

    homeWidget = new CBaseWidget(this);
    connect(homeWidget, SIGNAL(buttonClick()), this, SLOT(ProcHomeClick()));
    homeWidget->setGeometry(width - 115, 5, 50, 50);
    QImage homeWidgetTemp = QImage(":/res/image/if_Estate_home_house_building_property_real_1886940.png");
    homeWidget->setImage(0, homeWidgetTemp);
    homeWidget->hide();

    closeOffWidget = new CBaseWidget(this);
    connect(closeOffWidget, SIGNAL(buttonClick()), this, SLOT(ProcCloseOffClick()));
    closeOffWidget->setGeometry(width - 60, 5, 50, 50);
    QImage closeOffWidgetTemp = QImage(":/res/image/if_Close_1891023.png");
    closeOffWidget->setImage(0, closeOffWidgetTemp);
    closeOffWidget->hide();

    hiddenWidget = new QHidden(this);
    hiddenWidget->setGeometry(0,height-1, width, height);
    hiddenWidget->hide();

}


void MainWindow::ProcUpClick(){
    scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value()-100);
}

void MainWindow::ProcDownClick(){
    scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value()+100);
}


void MainWindow::ProcCloseOffClick(){

    statusHistoryEnabled = false;
    homeWidget->hide();
    closeOffWidget->hide();
    backWidget->hide();
    forwardWidget->hide();
    view->history()->clear();
    processClick(0);
}


void MainWindow::ProcHomeClick(){
    view->load(m_url);
}

void MainWindow::procSelectionChanged(){
    horizontalMenu->hide();
    hiddenWidget->show();
}


void MainWindow::procLoadUrlChanged(const QUrl&){
    if (statusHistoryEnabled){
        horizontalMenu->hide();
        hiddenWidget->show();
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

inline void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

void MainWindow::procLoadUrlFinished(bool s){
    delay(2000);
    view->setGeometry(0,0, width, height);
    view->show();
    view->update();
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
    delete centralMenu;
    delete horizontalMenu;
    delete parser;
    delete ui;
}

void MainWindow::processClick(int i){
    backWidget->hide();
    forwardWidget->hide();
    homeWidget->hide();
    closeOffWidget->hide();
    statusHistoryEnabled = false;
    centralMenu->hide();
    scroll->hide();
    backgroundImage->show();
    view->hide();

    tgroup xmlData = parser->getParsedData();
    QImage imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->background));
    backgroundImage->setImage(0,imgTmp);

    imgTmp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->icon));
    headerImageInfo->setImage(0, imgTmp);
    headerImageInfo->setTitleIcon(xmlData.categories.at(i)->name);
    headerImageInfo->show();
    downArrowWidget->show();
    upArrowWidget->show();

    if(xmlData.categories.at(i)->websites.count()!=0){
        downArrowWidget->show();
        upArrowWidget->show();
    }else{
        downArrowWidget->hide();
        upArrowWidget->hide();
    }

    centralMenu->createMenuByCategory(i);
    view->setGeometry(0,0, 0, 0);
    view->update();
    //view->setUrl(QUrl(QStringLiteral("https://player.vimeo.com/video/182513271?background=1")));
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
    htmlCont = htmlCont.replace("%url%",bgvideo);
    htmlCont = htmlCont.replace("%muted%",bgvideoSound);

    view->setHtml(htmlCont);

    view->show();

    backgroundImage->show();
    horizontalMenu->show();
    centralMenu->show();
    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
    scroll->show();
    scroll->setFocus();
}


void MainWindow::ProcClickForUrl(QString &url, QString &title){

    backWidget->hide();
    forwardWidget->hide();
    homeWidget->hide();
    closeOffWidget->hide();

    statusHistoryEnabled = true;
    centralMenu->hide();
    scroll->hide();
    backgroundImage->hide();
    view->setUrl(QUrl(url));
    m_url = url;
    view->show();

    scroll->setFocus();
//    scroll->verticalScrollBar()->setValue(0);
//    scroll->horizontalScrollBar()->setValue(0);
    downArrowWidget->hide();
    upArrowWidget->hide();

    headerImageInfo->setTitleIcon(title);

    headerImageInfo->show();
    horizontalMenu->hide();
    connect(hiddenWidget, SIGNAL(showStatus(bool)), this, SLOT(ProcShowHMenu(bool)));
    hiddenWidget->show();
    homeWidget->show();
    closeOffWidget->show();
    view->history()->clear();

}


void MainWindow::resizeEvent(QResizeEvent *event)
{
//    view->setGeometry(0,0, width, height-125);
    view->setGeometry(0,0, width, height);

    horizontalMenu->setGeometry(0, height-130, width, height);
    horizontalMenu->UpdateD(QRect(0, 0, width, 130));
    int tempNum = width/200;
    int tempWidth = (tempNum-1)*200;
    int tempMarg = (width-tempWidth)/2;

    centralMenu->setGeometry(QRect(tempMarg, 70, width-2*tempMarg, height-195));
    centralMenu->UpdateD(QRect(tempMarg, 70, width-2*tempMarg, height-195));
    view->hide();
    centralMenu->hide();
    QWidget::resizeEvent(event);
}

void MainWindow::ProcShowHMenu(bool s){
    if (s){
        horizontalMenu->show();
        hiddenWidget->hide();

    }

}

