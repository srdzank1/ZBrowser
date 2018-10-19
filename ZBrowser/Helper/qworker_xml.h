#ifndef QWORKER_H
#define QWORKER_H
#include <QUrlQuery>
#include <QWidget>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>



class QWorkerXml : public QWidget
{
    Q_OBJECT
public:
    explicit QWorkerXml(QWidget *parent = 0);
    ~QWorkerXml();
    void getList();

    int stat_finished;
    QString mStr;
private:
    QNetworkAccessManager *manager;
    QString urlhost;
    QString base64_decode(QString string);

signals:
    void finishedSearch();

public slots:
    void GetWebXMLForParse(QNetworkReply*);

};

#endif // QWORKER_H
