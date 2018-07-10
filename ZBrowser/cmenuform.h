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
    explicit CMenuForm(QWidget *parent, tgroup &data );
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
    CLargeImage *label[8][5];
    tgroup m_group;
signals:
    void clickForUrl(QString&);
};

#endif // CMENUFORM_H
