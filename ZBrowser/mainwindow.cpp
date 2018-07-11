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
    height = rec.height()*0.95;
    width = rec.width();

    backgroundImage = new CCentralBackgroundImage(this);
    backgroundImage->setGeometry(0,0, width, height);
    backgroundImage->setWidth(width);
    backgroundImage->setImage(0,QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ "images/0138dd49a38e8e64eb2a4738dba6dc4f_6478f.jpg")));
    backgroundImage->setHeight(height);
    backgroundImage->show();

    view = new QWebEngineView(this);
    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    connect(view->page(),
                &QWebEnginePage::fullScreenRequested,
                this,
                &MainWindow::fullScreenRequested);
    view->setUrl(QUrl("https://vimeo.com/182513271"));
    view->setGeometry(0,0, width, height);
    //view->show();

    parser = new CParserXML(this);
    QString filePath = "://res/xml/menu.xml";
    parser->loadThemeXmlFile(filePath);

    QFuture<int> future = QtConcurrent::run(parser, &CParserXML::CreateCashImage);

    tgroup xmlData = parser->getParsedData();

    headerImageInfo = new CHeaderImageInfo(this);
    headerImageInfo->setGeometry(5,5, width, 60);
    headerImageInfo->setWidth(50);
    headerImageInfo->setImage(0,QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(0)->icon)));
    headerImageInfo->setTitleIcon(xmlData.categories.at(0)->name);
    headerImageInfo->setHeight(50);
    headerImageInfo->show();



    horizontalMenu = new QHorizontalMenu(this, xmlData);

    horizontalMenu->setGeometry(0,height-120, width, height);
    connect(horizontalMenu, SIGNAL(click(int)), this, SLOT(processClick(int)));


    centralMenu = new CMenuForm(this, xmlData, width, height);
    connect(centralMenu, SIGNAL(clickForUrl(QString&)), this, SLOT(ProcClickForUrl(QString&)));
    centralMenu->setGeometry(0,0, width, height);
    centralMenu->hide();

    scroll = new QScrollArea(this);
    scroll->setStyleSheet("background-color:transparent; border: none;");
    scroll->setStyleSheet("QScrollArea {background-color:transparent;border: none;}");
    scroll->setGeometry(QRect(70, 70, width-140, height-195));
    scroll->verticalScrollBar()->setRange(0, height);
    scroll->horizontalScrollBar()->setRange(0, width);

    scroll->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    scroll->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    scroll->setWidget(centralMenu);
    scroll->setFocus();
    scroll->hide();

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
    centralMenu->close();
    scroll->hide();
    tgroup xmlData = parser->getParsedData();
    backgroundImage->setImage(0,QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->background)));
    backgroundImage->repaint();

    headerImageInfo->setImage(0,QImage(QDir::toNativeSeparators(QDir::currentPath() +"/"+ xmlData.categories.at(i)->icon)));
    headerImageInfo->setTitleIcon(xmlData.categories.at(i)->name);

    headerImageInfo->repaint();
    centralMenu->createMenuByCategory(i);
    view->setUrl(QUrl(QStringLiteral("")));
    view->hide();
    centralMenu->show();
    scroll->show();
    scroll->setFocus();
    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
}


void MainWindow::ProcClickForUrl(QString &url){

    centralMenu->close();
    scroll->hide();
    view->setUrl(QUrl(url));
    view->show();
    scroll->setFocus();
    scroll->verticalScrollBar()->setValue(0);
    scroll->horizontalScrollBar()->setValue(0);
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
//    view->setGeometry(0,0, width, height-125);
    view->setGeometry(0,0, width, height);

    horizontalMenu->setGeometry(0, height-125, width, height);
    horizontalMenu->UpdateD(QRect(0, 0, width, 125));

    centralMenu->setGeometry(0, 0, width*1.5, height*2);
    centralMenu->UpdateD(QRect(0, 0, width*1.5, height*2));
    view->hide();
    centralMenu->hide();
    QWidget::resizeEvent(event);
}
