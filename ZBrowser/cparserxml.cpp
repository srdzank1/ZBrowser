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
                    xmlReader.readElementText();
                }else if (xmlReader.name() == "GroupUrl"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    xmlReader.readElementText();
                } else if (xmlReader.name() == "GroupIcon"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    xmlReader.readElementText();
                } else if (xmlReader.name() == "GroupUniqueID"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    xmlReader.readElementText();
                } else if (xmlReader.name() == "version"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    xmlReader.readElementText();
                } else if (xmlReader.name() == "updatetime"){
                    QXmlStreamAttributes attribs = xmlReader.attributes();
                    xmlReader.readElementText();
                } else if (xmlReader.name() == "categories"){
                        while (xmlReader.readNextStartElement()){
                            if (xmlReader.name() == "category"){
                                while (xmlReader.readNextStartElement()){
                                    if (xmlReader.name() == "name"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "icon"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "background"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "updatetime"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "isupdated"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "bgvideo"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "videosound"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "videoopacity"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "textcolor"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "bartextcolor"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "barcolor"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "baropacity"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "tooltipcolor"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "arrowcolor"){
                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                        xmlReader.readElementText();
                                    }else if (xmlReader.name() == "websites"){
                                        while (xmlReader.readNextStartElement()){
                                            if (xmlReader.name() == "website"){
                                                while (xmlReader.readNextStartElement()){
                                                    if (xmlReader.name() == "id"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        QString id =  xmlReader.readElementText();
                                                        int stop = 0;
                                                    }else if (xmlReader.name() == "name"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "url"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "icon"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "type"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "allow"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "restriction"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "language"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "updatetime"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }else if (xmlReader.name() == "isupdated"){
                                                        QXmlStreamAttributes attribs = xmlReader.attributes();
                                                        xmlReader.readElementText();
                                                    }
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }
                }
            }
        }
    }


//    <name>Zac Browser</name>
//    <icon>images/0138dd49a38e8e64eb2a4738dba6dc4f_8d442.png</icon>
//    <background>images/0138dd49a38e8e64eb2a4738dba6dc4f_6478f.jpg</background>
//    <updatetime>2017-03-05 09:21:15</updatetime>
//    <isupdated>no</isupdated>
//    <bgvideo>https://vimeo.com/182513271</bgvideo>
//    <videosound>true</videosound>
//    <videoopacity>0</videoopacity>
//    <textcolor>#ffffff</textcolor>
//    <bartextcolor>#ffffff</bartextcolor>
//    <barcolor>#ffffff</barcolor>
//    <baropacity>0</baropacity>
//    <tooltipcolor/>
//    <arrowcolor>#ffffff</arrowcolor>
//    <websites> </websites>


    file.close();
    if (xmlReader.hasError())
    {
        qDebug() << "Error: Failed to parse file "
                 << qPrintable(xmlFile) << ": "
                 << qPrintable(xmlReader.errorString());
        return false;
    }
    else if (file.error() != QFile::NoError)
    {
        qDebug() << "Error: Cannot read file " << qPrintable(xmlFile)
                 << ": " << qPrintable(file.errorString());
        return false;
    }
    return true;
}
