#ifndef CLARGEIMAGE_H
#define CLARGEIMAGE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QRegion>
//#include <QSound>


class CLargeImage : public QWidget
{
    Q_OBJECT
public:
    explicit CLargeImage(QWidget *parent = nullptr);
    ~CLargeImage();

    void setImagePathName(int id, const QString& pathName);
    void setTitleIcon(const QString& name);
    void setUrl(const QString& url){m_url = url;}
    void setImage(int id, QImage & img );
    QImage getImage(){return mImage;}
    void setWidth(int w){m_width = w;}
    void setHeight(int h){m_height = h;}


protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
signals:
    void click(int);
    void clickForUrl(QString&,QString&, QImage&);
    void clickForEdit(int&);
public slots:
private:
    bool bmouseOver;
    QString m_pathName;
    int iItem;
    QString m_titleIcon;
    QImage mImage;
    QString m_url;
    QImage m_Icon;

    int m_width;
    int m_height;
    QBrush m_brush;
    bool statRepaint;
};


#endif // CLARGEIMAGE_H
