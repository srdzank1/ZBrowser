#ifndef CEDITWEBSITES_H
#define CEDITWEBSITES_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include "ccategorylistitems.h"
#include "ccategorylist.h"
#include <QScrollArea>
#include <QScrollBar>
#include "cbasewidget.h"


class CEditWebSites : public QWidget
{
    Q_OBJECT
public:
    explicit CEditWebSites(tgroup &data, QWidget *parent = nullptr);
    ~CEditWebSites();
    void menuGlobalSettings();
    void setFilters(tfilterwebsite &efilter);
    void getFilters(tfilterwebsite &efilter);
    void setFiltersCategory(tfiltercategory &efilter);
    void getFiltersCategory(tfiltercategory &efilter);
    void FuncChangeCategory(int& i, tfilterwebsite &efilter);


protected:
    void paintEvent(QPaintEvent *event);
signals:
    void webSitesChangeCategory(int &i);
    void closeWebSites();
    void updateHorizMenu();
public slots:
    void procChangeCategory(int& i);
    void ProcCloseWebSites();
    void procUpdateHorizontalMenu();

private:
    void CreateCloseOffWidget();
    QLabel * webEdit;
    CCategoryList *categ;
    CCategoryListItems *categItems;
    tgroup m_group;
    int m_w;
    int m_h;
    QScrollArea *scroll;
    QScrollArea *categScroll;
    QWidget * blank;
    CBaseWidget *closeOffWidget;
};

#endif // CEDITWEBSITES_H
