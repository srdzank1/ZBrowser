#ifndef CSCHEDULE_H
#define CSCHEDULE_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QList>
#include "cbasewidget.h"

#include "XMLParser/cparserxml.h"

typedef struct{
    int day;
    int hour;
    int min;
    QRect rect;
    bool stat;
} tschedulate;

typedef QList<QString> tfilterschedule;

class CSchedule : public QWidget
{
    Q_OBJECT
public:
    explicit CSchedule(tgroup &data, QWidget *parent = nullptr);
    ~CSchedule();
    void menuGlobalSettings();
    int GetSchedulateDays();
    QList<int> GetSchedulateHoursByDay(int day);

    void getFilterSchedule(tfilterschedule &data);
    void setFilterSchedule(tfilterschedule &data);
protected:
    void paintEvent(QPaintEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
signals:
    void closeWebSites();

public slots:
    void ProcCloseWebSites();
private:
    void createForm(QPainter &painter);
    void deleteLSch();
    void createHoursLabel(QPainter &painter);
    void createWeekLabel(QPainter &painter);
    void createBlockedIntervals(int day, int hours, QPainter &painter);
    void createBasicBlock(QPainter &painter, const int &x, const int &y, const int &w, const int &h, bool status);
    void createScheduleList();
    void CreateCloseOffWidget();

    QLabel * editSchedule;
    tgroup m_group;
    int SchWidth;
    int SchHeight;
    QList<tschedulate*> lSchedule;
    int posX;
    int posY;
    int offset;
    int calH;
    int calD;
    int stepX;
    int stepY;
    CBaseWidget *closeOffWidget;

};

#endif // CSCHEDULE_H
