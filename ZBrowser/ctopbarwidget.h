#ifndef CTOPBARWIDGET_H
#define CTOPBARWIDGET_H

#include <QWidget>
#include <QPainter>

class CTopBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CTopBarWidget(QWidget *parent = 0);
    ~CTopBarWidget();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CTOPBARWIDGET_H
