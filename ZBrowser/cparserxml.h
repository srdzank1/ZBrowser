#ifndef CPARSERXML_H
#define CPARSERXML_H

#include <QWidget>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include <qDebug>

class CParserXML : public QWidget
{
    Q_OBJECT
public:
    explicit CParserXML(QWidget *parent = nullptr);
    bool loadThemeXmlFile(const QString &xmlFile);
;
signals:

public slots:
private:
    QString  m_xmlFile;
    QString m_themeName;
    QString m_bkgFileName;
    QString m_type;
};

#endif // CPARSERXML_H
