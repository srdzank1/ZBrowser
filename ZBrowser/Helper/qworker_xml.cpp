#include "qworker_xml.h"

QWorkerXml::QWorkerXml(QWidget *parent) : QWidget(parent)
  ,stat_finished(0)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(GetWebXMLForParse(QNetworkReply*)));
}

QWorkerXml::~QWorkerXml()
{
    delete manager;
}


QString QWorkerXml::base64_decode(QString string)
{
    QByteArray ba;
    ba.append(string);
    return QByteArray::fromBase64(ba);
}

void QWorkerXml::getList()
{
    QUrl serviceUrl = QUrl("http://zacbrowser.com/10/Free/235kkj324.xml");
    QNetworkRequest req;
    req.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    req.setUrl(serviceUrl);
    req.setRawHeader( "User-Agent", "Mozilla/5.0 (X11; U; Linux i686 (x86_64); "
                               "en-US; rv:1.9.0.1) Gecko/2008070206 Firefox/3.0.1" );
    req.setRawHeader( "charset", "utf-8" );
    req.setRawHeader( "Connection", "keep-alive" );
    manager->get(req);
}
void QWorkerXml::GetWebXMLForParse(QNetworkReply *rep)
{
    QByteArray bts = rep->readAll();

    QString str(bts);
    mStr = str;
    bts.clear();
    emit finishedSearch();
}





