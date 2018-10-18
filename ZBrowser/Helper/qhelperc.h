#ifndef QHELPERC_H
#define QHELPERC_H
#include <QWidget>
#include "Helper/qworker_xml.h"
#include <QEventLoop>

//

class QHelperC : public QWidget
{
    Q_OBJECT
public:
    explicit QHelperC(QWidget *parent = 0);
    ~QHelperC();
    QString getWebXML();

private:

signals:

private slots:


};

#endif // QHELPERC_H
