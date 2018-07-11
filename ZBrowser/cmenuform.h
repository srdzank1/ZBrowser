#ifndef CMENUFORM_H
#define CMENUFORM_H

#include <QWidget>
//#include "simagewidget.h"
#include "cparserxml.h"
#include "clargeimage.h"

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
    void createMenuByCategory(int id);
protected:
    virtual bool event(QEvent *event);
public slots:
    void processClick(int i);
    void processClickForUrl(QString&);
private:
    Ui::CMenuForm *ui;
    tgroup m_group;
    int m_width;
    int m_height;

    int xOffset;
    int yOffset;
    QList<CLargeImage*> pListLargeImage;
    CLargeImage * pLargeImage;
signals:
    void clickForUrl(QString&);
};

#endif // CMENUFORM_H
