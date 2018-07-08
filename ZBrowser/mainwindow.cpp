#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QRect rec = QApplication::desktop()->screenGeometry();
    height = rec.height()*0.95;
    width = rec.width();

    CParserXML *parser = new CParserXML(this);
    QString filePath = "://res/xml/menu.xml";
    parser->loadThemeXmlFile(filePath);
    tgroup xmlData = parser->getParsedData();
    delete parser;

//    view = new QWebEngineView(this);
//    view->setUrl(QUrl(QStringLiteral("https://youtu.be/qQKPFJ2y-_w")));
//    view->setGeometry(0,0, width, height);
//    view->show();

    horizontalMenu = new QHorizontalMenu(this, xmlData);

    horizontalMenu->setGeometry(0,height-90, width, height);
    connect(horizontalMenu, SIGNAL(click(int)), this, SLOT(processClick(int)));

    centralMenu = new CMenuForm(this);
    centralMenu->setGeometry(100,100, width-100, height-150);
    centralMenu->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processClick(int i){
    centralMenu->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    view->setGeometry(0,0, width, height);
    horizontalMenu->setGeometry(0, height-90, width, height);
    horizontalMenu->UpdateD(QRect(0, 0, width, 80));

    centralMenu->setGeometry(100,100, width-100, height-150);
    centralMenu->UpdateD(QRect(100,100, width-100, height-150));
    QWidget::resizeEvent(event);
}
