#ifndef CLARGEIMAGEEDITCATEGORY_H
#define CLARGEIMAGEEDITCATEGORY_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
//#include <QSound>


class CLargeImageEditCategory : public QWidget
{
    Q_OBJECT
public:
    explicit CLargeImageEditCategory(QWidget *parent = nullptr);
    ~CLargeImageEditCategory();

    void setImagePathName(int id, const QString& pathName);
    void setTitleIcon(const QString& name);
    void setUrl(const QString& url){m_url = url;}
    void setImage(int id, QImage & img );
    QImage getImage(){return mImage;}
    void setWidth(int w){m_width = w;}
    void setHeight(int h){m_height = h;}
    void setStatus(bool stat){m_clickedStatus = stat;}
    bool getStatus(){return m_clickedStatus;}
    void setId(QString id){m_titleIcon = id;}
    QString getId(){return m_titleIcon;}

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void mouseDoubleClickEvent( QMouseEvent * e );
signals:
    void click(int);
    void clickForUrl(QString&,QString&, QImage&);
    void clickForEdit(int&);
    void updateHorizontalMenu();
public slots:
private:
    bool bmouseOver;
    QString m_pathName;
    int iItem;
    QString m_titleIcon;
    QImage mImage;
    QString m_url;
    QImage m_Icon;
    QString m_ID;
    QImage m_imagePlus;
    QImage m_imageMinus;

    int m_width;
    int m_height;
    QBrush m_brush;
    bool statRepaint;
    bool m_clickedStatus;
};


#endif // CLARGEIMAGEEDITCATEGORY_H
