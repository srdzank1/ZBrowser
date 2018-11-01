#include "qhelperc.h"


QHelperC::QHelperC(QWidget *parent) : QWidget(parent)
{
}

QHelperC::~QHelperC()
{

}
//-----------------------------artikli-------------------------------------------------
QString QHelperC::getWebXML()
{
    QEventLoop pause;
    QWorkerXml worker;
    connect(&worker, SIGNAL(finishedSearch()), &pause, SLOT(quit()));
    QString url = "http://zacbrowser.com/10/Free/235kkj324.xml";
    worker.getList(url);
    pause.exec();
    return worker.mStr;
}

QByteArray QHelperC::getWebImage(QString & imgUrl)
{
    QEventLoop pause;
    QWorkerXml worker;
    connect(&worker, SIGNAL(finishedSearch()), &pause, SLOT(quit()));
    worker.getImage(imgUrl);
    pause.exec();
    return worker.mData;
}
