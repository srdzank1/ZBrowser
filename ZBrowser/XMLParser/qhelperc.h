#ifndef QHELPERC_H
#define QHELPERC_H
#include <QWidget>
#include "XMLParser/qworker_xml.h"
#include <QEventLoop>


//

class QHelperC : public QWidget
{
    Q_OBJECT
public:
    explicit QHelperC(QWidget *parent = 0);
    ~QHelperC();
    QString getWebXML();
    QByteArray getWebImage(QString & imgUrl);

private:

signals:

private slots:


};

#endif // QHELPERC_H
