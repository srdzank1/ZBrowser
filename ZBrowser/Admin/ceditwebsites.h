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

typedef struct {
   QString  id;
   bool hide;
} tfilterwebsite;

typedef struct {
   QList<tfilterwebsite*> filteredWebsites;
} tfilter;


class CEditWebSites : public QWidget
{
    Q_OBJECT
public:
    explicit CEditWebSites(tgroup &data, QWidget *parent = nullptr);
    ~CEditWebSites();
    void menuGlobalSettings();
    void setFilters(tfilter &efilter);
    void getFilters(tfilter &efilter);

protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void procChangeCategory(int& i);
private:
    QLabel * webEdit;
    CCategoryList *categ;
    CCategoryListItems *categItems;
    tgroup m_group;
    int m_w;
    int m_h;
    QScrollArea *scroll;
    QScrollArea *categScroll;
    QWidget * blank;
};

#endif // CEDITWEBSITES_H
