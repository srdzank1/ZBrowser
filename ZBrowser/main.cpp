#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngine/QtWebEngine>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWebEngine::initialize();
    MainWindow w;
    w.initVideo();
    w.showFullScreen();
//    w.showMaximized();

    return a.exec();
}
