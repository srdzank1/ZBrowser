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
//    worker.getList();
    pause.exec();
    return "";
}

