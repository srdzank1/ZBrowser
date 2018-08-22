#ifndef CLOADERWIDGET_H
#define CLOADERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class CLoaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLoaderWidget(QWidget *parent = nullptr);
    ~CLoaderWidget();
    void setValue(int v){
        m_value = v;
        repaint();
    }
protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_value;
};

#endif // CLOADERWIDGET_H
