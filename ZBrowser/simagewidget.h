#ifndef SIMAGEWIDGET_H
#define SIMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
//#include <QSound>


class SImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SImageWidget(QWidget *parent = nullptr);
    void setImagePathName(int id, const QString& pathName);
    void setTitleIcon(const QString& name);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
signals:
    void click(int);
public slots:
private:
    bool bmouseOver;
    QString m_pathName;
    int iItem;
    QString m_titleIcon;
    QImage mImage;
    int m_x;
    int m_y;
};

#endif // SIMAGEWIDGET_H
