#ifndef CSWITCH_H
#define CSWITCH_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>

class CSwitch : public QWidget
{
    Q_OBJECT
public:
    explicit CSwitch(QWidget *parent = nullptr);
    bool GetStatus(){return statOn;}
    void SetStatus(bool &eStatOn){statOn = eStatOn;}
protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
signals:
    void changeSwitchStatus(bool);
    void changeEnableRestriction();
    void changeEnableSchedule();
public slots:
private:
    QImage mOnImage;
    QImage mOffImage;
    bool statOn ;
};

#endif // CSWITCH_H
