#ifndef CPARSERXML_H
#define CPARSERXML_H

#include <QWidget>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QImage>
#include <QImageReader>
#include <QMutex>
#define SUBDIR "/images/"
//#define SUBDIR "/"



typedef struct {
   QString  id;
   QString  name;
   QString  url;
   QString  icon;
   QImage  iconImage;
   bool    iconImageCash;
   QString  type;
   QString  allow;
   QString  restriction;
   QString  language;
   QString  updatetime;
   QString  isupdated;
   bool hide;
} twebsite;

typedef struct {
   QString  name;
   QString  icon;
   QString  background;
   QString  updatetime;
   QString  isupdated;
   QString  bgvideo;
   QString  videosound;
   QString  videoopacity;
   QString  textcolor;
   QString  bartextcolor;
   QString  barcolor;
   QString  baropacity;
   QString  tooltipcolor;
   QString  arrowcolor;
   QList<twebsite*> websites;
} tcategory;

typedef struct {
   QString  name;
   QString  url;
   QString  icon;
   QString  uniqueid;
   QString  version;
   QString  updatetime;
   QList<tcategory*> categories;
} tgroup;



class CParserXML : public QWidget
{
    Q_OBJECT
public:
    explicit CParserXML(QWidget *parent = nullptr);
    bool loadThemeXmlFile(const QString &xmlFile);
    bool SetXmlThemeXmlFile(const QString &xmlString);
    tgroup getParsedData(){return m_group;}
    void setParsedData(tgroup & a_group){m_group = a_group;}

    int CreateCashImage();

signals:

public slots:
private:
    QString  m_xmlFile;
    tgroup m_group;
};

#endif // CPARSERXML_H
