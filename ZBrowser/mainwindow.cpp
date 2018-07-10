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

    view = new QWebEngineView(this);
    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
//    view->setUrl(QUrl(QStringLiteral("https://youtu.be/qQKPFJ2y-_w")));
    connect(view->page(),
                &QWebEnginePage::fullScreenRequested,
                this,
                &MainWindow::fullScreenRequested);
    view->setUrl(QUrl(""));
    view->setGeometry(0,0, width, height);
    view->show();

    parser = new CParserXML(this);
    QString filePath = "://res/xml/menu.xml";
    parser->loadThemeXmlFile(filePath);
//    parser->CreateCashImage();
    // call 'void QImage::invertPixels(InvertMode mode)' in a separate thread

    QFuture<int> future = QtConcurrent::run(parser, &CParserXML::CreateCashImage);


    tgroup xmlData = parser->getParsedData();


    horizontalMenu = new QHorizontalMenu(this, xmlData);

    horizontalMenu->setGeometry(0,height-120, width, height);
    connect(horizontalMenu, SIGNAL(click(int)), this, SLOT(processClick(int)));

    centralMenu = new CMenuForm(this, xmlData);
    connect(centralMenu, SIGNAL(clickForUrl(QString&)), this, SLOT(ProcClickForUrl(QString&)));
    centralMenu->setGeometry(20,20, width-20, height-150);
    centralMenu->hide();
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
    centralMenu->createMenuByCategory(i);
    view->setUrl(QUrl(QStringLiteral("")));
    view->hide();
    centralMenu->show();
}


void MainWindow::ProcClickForUrl(QString &url){
    centralMenu->close();
    view->setUrl(QUrl(url));
    view->show();
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    view->setGeometry(0,0, width, height-125);
    horizontalMenu->setGeometry(0, height-125, width, height);
    horizontalMenu->UpdateD(QRect(0, 0, width, 125));

    centralMenu->setGeometry(150, 50, width-300, height-170);
    centralMenu->UpdateD(QRect(150, 50, width-300, height-170));
    QWidget::resizeEvent(event);
}
