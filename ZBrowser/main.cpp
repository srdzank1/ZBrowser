#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngine/QtWebEngine>

int main(int argc, char *argv[])
{
    argv[1] = (char*)"--ppapi-flash-path=./pepflashplayer64_30_0_0_134.dll";
    QApplication a(argc, argv);
    QtWebEngine::initialize();
    MainWindow w;
    w.LoadXMLFileFromURLInit();
    w.initVideo();
    w.CreateInitElement();
//    w.InitXMLGrabber();

    w.showFullScreen();
//    w.showMaximized();

    return a.exec();
}
