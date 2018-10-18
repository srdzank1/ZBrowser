#ifndef QWORKER_H
#define QWORKER_H
#include <QUrlQuery>
#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QNetworkAccessManager>



class QWorkerXml : public QWidget
{
    Q_OBJECT
public:
    explicit QWorkerXml(QWidget *parent = 0);
    void getList();

    int stat_finished;
private:
    QNetworkAccessManager networkManager;
    QString urlhost;
    QString base64_decode(QString string);

signals:
    void finishedSearch();

public slots:
    void onPostList(QNetworkReply *rep);

};

#endif // QWORKER_H
