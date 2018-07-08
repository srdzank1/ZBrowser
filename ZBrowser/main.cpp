#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngine/QtWebEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QtWebEngine::initialize();
    w.showMaximized();
    return a.exec();
}
