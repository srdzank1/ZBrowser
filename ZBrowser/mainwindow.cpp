#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QRect rec = QApplication::desktop()->screenGeometry();
    height = rec.height();
    width = rec.width();


    view = new QWebEngineView(this);
    view->setUrl(QUrl(QStringLiteral("https://youtu.be/qQKPFJ2y-_w")));
    view->setGeometry(0,0, width, height-50);
    view->show();


    customerList = new QHorizontalMenu(this);
    customerList->setGeometry(0,height-50, width, height);
    connect(customerList, SIGNAL(click(int)), this, SLOT(processClick(int)));

    centralMainFormS = new CMenuForm(this);
    centralMainFormS->setGeometry(100,100, width-100, height-150);
    centralMainFormS->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processClick(int i){
    centralMainFormS->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    view->setGeometry(0,0, ui->centralWidget->width(), ui->centralWidget->height()-50);
    customerList->setGeometry(0,ui->centralWidget->height()-50, ui->centralWidget->width(), ui->centralWidget->height());
    customerList->UpdateD(QRect(0, 0, ui->centralWidget->width(), 50));

    centralMainFormS->setGeometry(100,100, width-100, height-150);
    centralMainFormS->UpdateD(QRect(100,100, width-100, height-150));
    QWidget::resizeEvent(event);
}
