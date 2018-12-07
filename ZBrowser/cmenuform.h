#ifndef CMENUFORM_H
#define CMENUFORM_H

#include <QWidget>
//#include "simagewidget.h"
#include "XMLParser/cparserxml.h"
#include "clargeimage.h"
#include "ccategorylistitems.h"
#include "Admin/cadminsettingswidget.h"
#include <QSound>


#include "QDir"

namespace Ui {
class CMenuForm;
}

class CMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit CMenuForm(QWidget *parent, tgroup &data, int &width, int&height );
    ~CMenuForm();
    void UpdateD(QRect r);
    void createMenuByCategory(int id, tfilterwebsite &mFilteredWeb, tsettings &mSettings);
    void setXMLData(tgroup &data){m_group = data;}
protected:
    virtual bool event(QEvent *event);
public slots:
    void processClickForUrl(QString&, QString&, QImage&);
    int getRowMax(){return mRowCount;}
private:
    Ui::CMenuForm *ui;
    tgroup m_group;
    int m_width;
    int m_height;

    int xOffset;
    int yOffset;
    int mRowCount;
    QList<CLargeImage*> pListLargeImage;
    CLargeImage * pLargeImage;
signals:
    void clickForUrl(QString&, QString&, QImage&);
};

#endif // CMENUFORM_H
