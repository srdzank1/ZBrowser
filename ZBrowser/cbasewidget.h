#ifndef CBASEWIDGET_H
#define CBASEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class CBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CBaseWidget(QWidget *parent = nullptr);
    ~CBaseWidget();

    void setImagePathName(int id, const QString& pathName);
    void setImage(int id, QImage & img );
    QImage getImage(){return mImage;}
    void setWidth(int w){m_width = w;}
    void setHeight(int h){m_height = h;}
    void setTitleIcon(const QString& name);



protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);

    virtual void mouseReleaseEvent(QMouseEvent * event);
signals:
    void buttonClick();
public slots:
private:
    QString m_pathName;
    int iItem;
    QImage mImage;
    int m_width;
    int m_height;
    QBrush m_brush;
    QString m_titleIcon;
    bool bmouseOver;
};

#endif // CBASEWIDGET_H