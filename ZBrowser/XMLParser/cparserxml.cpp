#include "cparserxml.h"

CParserXML::CParserXML(QWidget *parent) : QWidget(parent)
{

}

bool CParserXML::loadThemeXmlFile(const QString &xmlFile)
{
    QFile file(xmlFile);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(NULL, "Error", QString("Couldn't open '%1' file").arg(xmlFile));
        return false;
    }
    m_xmlFile = xmlFile;
    QXmlStreamReader xmlReader(&file);
    if (xmlReader.readNextStartElement())
    {
        if(xmlReader.name() == "Group")
        {
            while (xmlReader.readNextStartElement())
            {
                if (xmlReader.name() == "GroupName"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.name = xmlReader.readElementText();
                }else if (xmlReader.name() == "GroupUrl"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.url = xmlReader.readElementText();
                } else if (xmlReader.name() == "GroupIcon"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.icon = xmlReader.readElementText();
                } else if (xmlReader.name() == "GroupUniqueID"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.uniqueid = xmlReader.readElementText();
                } else if (xmlReader.name() == "version"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.version = xmlReader.readElementText();
                } else if (xmlReader.name() == "updatetime"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.updatetime = xmlReader.readElementText();
                } else if (xmlReader.name() == "categories"){
                    QList<tcategory*> listCategory;
                    while (xmlReader.readNextStartElement()){
                            if (xmlReader.name() == "category"){
                               tcategory *categoryItem = new tcategory;
                                while (xmlReader.readNextStartElement()){
                                    if (xmlReader.name() == "name"){
                                        categoryItem->name = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "icon"){
                                        categoryItem->icon = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "background"){
                                        categoryItem->background = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "updatetime"){
                                        categoryItem->updatetime = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "isupdated"){
                                        categoryItem->isupdated = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "bgvideo"){
                                        categoryItem->bgvideo = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "videosound"){
                                        categoryItem->videosound = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "videoopacity"){
                                        categoryItem->videoopacity = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "textcolor"){
                                        categoryItem->textcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "bartextcolor"){
                                        categoryItem->bartextcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "barcolor"){
                                        categoryItem->barcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "baropacity"){
                                        categoryItem->baropacity = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "tooltipcolor"){
                                        categoryItem->tooltipcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "arrowcolor"){
                                        categoryItem->arrowcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "websites"){
                                        QList<twebsite*> listWebsites;
                                        while (xmlReader.readNextStartElement()){
                                            if (xmlReader.name() == "website"){
                                                twebsite* websiteItem = new twebsite;
                                                while (xmlReader.readNextStartElement()){
                                                    if (xmlReader.name() == "id"){
                                                       websiteItem->id = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "name"){
                                                       websiteItem->name = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "url"){
                                                       websiteItem->url = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "icon"){
                                                       websiteItem->icon = xmlReader.readElementText();
                                                       websiteItem->iconImageCash = 0;
//                                                       QString iconPath = QDir::toNativeSeparators(QDir::currentPath() +"/"+ websiteItem->icon);
//                                                       websiteItem->iconImage = QImage(iconPath);
                                                    }else if (xmlReader.name() == "type"){
                                                       websiteItem->type = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "allow"){
                                                       websiteItem->allow = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "restriction"){
                                                       websiteItem->restriction = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "language"){
                                                       websiteItem->language = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "updatetime"){
                                                       websiteItem->updatetime = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "isupdated"){
                                                       websiteItem->isupdated = xmlReader.readElementText();
                                                    }
                                                }
                                                listWebsites.append(websiteItem);
                                            }
                                        }
                                        categoryItem->websites = listWebsites;
                                    }
                                }
                                listCategory.append(categoryItem);
                            }
                        }
                    m_group.categories = listCategory;
                    int stop = 0;
                }
            }
        }
    }

    file.close();
    if (xmlReader.hasError())
    {
//        qDebug() << "Error: Failed to parse file "
//                 << qPrintable(xmlFile) << ": "
//                 << qPrintable(xmlReader.errorString());
        return false;
    }
    else if (file.error() != QFile::NoError)
    {
//        qDebug() << "Error: Cannot read file " << qPrintable(xmlFile)
//                 << ": " << qPrintable(file.errorString());
        return false;
    }
    return true;
}

bool CParserXML::SetXmlThemeXmlFile(const QString &xmlString)
{
    QXmlStreamReader xmlReader(xmlString);
    if (xmlReader.readNextStartElement())
    {
        if(xmlReader.name() == "Group")
        {
            while (xmlReader.readNextStartElement())
            {
                if (xmlReader.name() == "GroupName"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.name = xmlReader.readElementText();
                }else if (xmlReader.name() == "GroupUrl"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.url = xmlReader.readElementText();
                } else if (xmlReader.name() == "GroupIcon"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.icon = xmlReader.readElementText();
                } else if (xmlReader.name() == "GroupUniqueID"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.uniqueid = xmlReader.readElementText();
                } else if (xmlReader.name() == "version"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.version = xmlReader.readElementText();
                } else if (xmlReader.name() == "updatetime"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    m_group.updatetime = xmlReader.readElementText();
                } else if (xmlReader.name() == "categories"){
                    QList<tcategory*> listCategory;
                    while (xmlReader.readNextStartElement()){
                            if (xmlReader.name() == "category"){
                               tcategory *categoryItem = new tcategory;
                                while (xmlReader.readNextStartElement()){
                                    if (xmlReader.name() == "name"){
                                        categoryItem->name = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "icon"){
                                        categoryItem->icon = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "background"){
                                        categoryItem->background = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "updatetime"){
                                        categoryItem->updatetime = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "isupdated"){
                                        categoryItem->isupdated = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "bgvideo"){
                                        categoryItem->bgvideo = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "videosound"){
                                        categoryItem->videosound = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "videoopacity"){
                                        categoryItem->videoopacity = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "textcolor"){
                                        categoryItem->textcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "bartextcolor"){
                                        categoryItem->bartextcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "barcolor"){
                                        categoryItem->barcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "baropacity"){
                                        categoryItem->baropacity = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "tooltipcolor"){
                                        categoryItem->tooltipcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "arrowcolor"){
                                        categoryItem->arrowcolor = xmlReader.readElementText();
                                    }else if (xmlReader.name() == "websites"){
                                        QList<twebsite*> listWebsites;
                                        while (xmlReader.readNextStartElement()){
                                            if (xmlReader.name() == "website"){
                                                twebsite* websiteItem = new twebsite;
                                                while (xmlReader.readNextStartElement()){
                                                    if (xmlReader.name() == "id"){
                                                       websiteItem->id = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "name"){
                                                       websiteItem->name = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "url"){
                                                       websiteItem->url = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "icon"){
                                                       websiteItem->icon = xmlReader.readElementText();
                                                       websiteItem->iconImageCash = 0;
//                                                       QString iconPath = QDir::toNativeSeparators(QDir::currentPath() +"/"+ websiteItem->icon);
//                                                       websiteItem->iconImage = QImage(iconPath);
                                                    }else if (xmlReader.name() == "type"){
                                                       websiteItem->type = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "allow"){
                                                       websiteItem->allow = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "restriction"){
                                                       websiteItem->restriction = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "language"){
                                                       websiteItem->language = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "updatetime"){
                                                       websiteItem->updatetime = xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "isupdated"){
                                                       websiteItem->isupdated = xmlReader.readElementText();
                                                    }
                                                }
                                                listWebsites.append(websiteItem);
                                            }
                                        }
                                        categoryItem->websites = listWebsites;
                                    }
                                }
                                listCategory.append(categoryItem);
                            }
                        }
                    m_group.categories = listCategory;
                    int stop = 0;
                }
            }
        }
    }


    if (xmlReader.hasError())
    {
//        qDebug() << "Error: Failed to parse file "
//                 << qPrintable(xmlFile) << ": "
//                 << qPrintable(xmlReader.errorString());
        return false;
    }
    return true;
}

int CParserXML::CreateCashImage(){
    QImage * imgObj = new QImage();
    for(int i = 0; i < m_group.categories.count(); i++){
        tcategory *item = m_group.categories.at(i);
        for (int j = 0; j < item->websites.count(); j++){
            twebsite *webItem = item->websites.at(j);
            if (webItem->iconImageCash == 0){
                webItem->iconImage = QImage(QDir::toNativeSeparators(QDir::currentPath() +SUBDIR+ webItem->icon)).scaled(200, 187, Qt::KeepAspectRatio, Qt::FastTransformation);
                webItem->iconImageCash = 1;
            }
        }
    }
    return 0;
}




