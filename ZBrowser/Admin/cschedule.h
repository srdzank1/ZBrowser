#ifndef CSCHEDULE_H
#define CSCHEDULE_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include "XMLParser/cparserxml.h"

class CSchedule : public QWidget
{
    Q_OBJECT
public:
    explicit CSchedule(tgroup &data, QWidget *parent = nullptr);
    ~CSchedule();
    void menuGlobalSettings();

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
private:
    void createForm(QPainter &painter);
    QLabel * editSchedule;
    tgroup m_group;

};

#endif // CSCHEDULE_H
