#include "qworker_xml.h"

QWorkerXml::QWorkerXml(QWidget *parent) : QWidget(parent)
  ,stat_finished(0)
{
//    Singleton *s = Singleton::Instance();
//    urlhost = s->Get_UrlHost();
}

QString QWorkerXml::base64_decode(QString string)
{
    QByteArray ba;
    ba.append(string);
    return QByteArray::fromBase64(ba);
}

void QWorkerXml::getList()
{
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onPostList(QNetworkReply*)));
    networkManager.clearAccessCache();
    QUrl serviceUrl = QUrl(urlhost + "get_article_list");

//    Singleton *s = Singleton::Instance();
//    QByteArray HeaderVar = "Authorization";
//    QByteArray HeaderValue = s->getToken().toUtf8();



//    QByteArray postData;

//    QJsonObject tt_json;
//    tt_json["offset"] = vOffset;
//    tt_json["limit"] = vLimit;
//    tt_json["search_name"] = vSearchName;
//    tt_json["search_by"] = vSearchBy;

//    QJsonDocument doc(tt_json);
//    QByteArray tt = doc.toJson();


//    postData.append(tt);
//    QNetworkRequest networkRequest(serviceUrl);
//    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
//    networkRequest.setRawHeader(HeaderVar, HeaderValue );
//    networkManager.post(networkRequest,postData);
//    HeaderVar.clear();
//    HeaderValue.clear();
//    postData.clear();

}
void QWorkerXml::onPostList(QNetworkReply *rep)
{
    disconnect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onPostList(QNetworkReply*)));
//    QByteArray bts = rep->readAll();
//    QString str(bts);
//    bts.clear();
//    QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
//    QJsonObject jsonObject = jsonResponse.object();
//    QJsonArray jsonArray = jsonObject["properties"].toArray();



//    for (int a = 0; a < jsonArray.count(); a++)
//    {
//        artikalT art_temp;
//        const QJsonValue & value = jsonArray.at(a);
//        QJsonObject obj = value.toObject();
//        art_temp.id = (obj["id"].toString());
//        art_temp.sifra = (obj["sifra"].toString());
//        art_temp.artikal = (obj["artikal"].toString());
//        art_temp.edm = (obj["edm"].toString());
//        art_temp.ref = (obj["ref"].toString());
//        art_temp.kataloski_broj = (obj["kataloski_broj"].toString());
//        art_temp.ddv = (obj["ddv"].toString());
//        art_temp.proizvoditel = (obj["proizvoditel"].toString());
//        art_temp.kategorija = (obj["kategorija"].toString());


//        if(art_temp.id == "end")
//        {
//            continue;
//        }
//        else
//        {
//            listRes << art_temp ;
//        }
//    }
    emit finishedSearch();
}





