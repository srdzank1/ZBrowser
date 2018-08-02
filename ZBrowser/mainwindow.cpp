#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    connect(view->page(),
                &QWebEnginePage::fullScreenRequested,
                this,
                &MainWindow::fullScreenRequested);

    view->setUrl(QUrl(QStringLiteral("https://player.vimeo.com/video/182513271?background=1&muted=0")));
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
    headerImageInfo->hide();



    horizontalMenu = new QHorizontalMenu(this, xmlData);
    horizontalMenu->setGeometry(0,height-120, width, height);
    connect(horizontalMenu, SIGNAL(click(int)), this, SLOT(processClick(int)));

    int tempNum = width/200;
    int tempWidth = (tempNum-1)*200;
    int tempMarg = (width-tempWidth)/2;

    centralMenu = new CMenuForm(this, xmlData, tempWidth, height);
    connect(centralMenu, SIGNAL(clickForUrl(QString&)), this, SLOT(ProcClickForUrl(QString&)));
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
    upArrowWidget->setGeometry(width - 68, 70, 50, 50);
    QImage upArrowTemp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ "images/top.png"));
    upArrowWidget->setImage(0, upArrowTemp);
    upArrowWidget->show();

    downArrowWidget = new CBaseWidget(this);
    downArrowWidget->setGeometry(width - 68, height-175, 50, 50);
    QImage downArrowTemp = QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ "images/bottom.png"));
    downArrowWidget->setImage(0, downArrowTemp);
    downArrowWidget->show();

    scroll->hide();
    backgroundImage->hide();
    centralMenu->hide();

    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
    scroll->hide();
    scroll->setFocus();
    backgroundImage->show();

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
    downArrowWidget->show();
    upArrowWidget->show();


    centralMenu->createMenuByCategory(i);
    view->setGeometry(0,0, 0, 0);
    view->update();
    //view->setUrl(QUrl(QStringLiteral("https://player.vimeo.com/video/182513271?background=1")));
    QString bgvideo = xmlData.categories.at(i)->bgvideo;
    bgvideo = bgvideo.trimmed();
    bgvideo += "?background=1&muted=0";
    //bgvideo += "?autoplay=1&loop=1&title=0&byline=0&portrait=0";
    view->setUrl(QUrl(bgvideo));

    view->show();

    backgroundImage->show();
    centralMenu->show();
    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
    scroll->show();
    scroll->setFocus();
}


void MainWindow::ProcClickForUrl(QString &url){

    centralMenu->hide();
    scroll->hide();
    backgroundImage->hide();
    view->setUrl(QUrl(url));
    view->show();

    scroll->setFocus();
//    scroll->verticalScrollBar()->setValue(0);
//    scroll->horizontalScrollBar()->setValue(0);
    downArrowWidget->hide();
    upArrowWidget->hide();
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


