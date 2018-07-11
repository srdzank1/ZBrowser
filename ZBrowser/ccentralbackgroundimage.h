#ifndef CCENTRALBACKGROUNDIMAGE_H
#define CCENTRALBACKGROUNDIMAGE_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>


class CCentralBackgroundImage : public QWidget
{
    Q_OBJECT
public:
    explicit CCentralBackgroundImage(QWidget *parent = nullptr);
    ~CCentralBackgroundImage();

    void setImagePathName(int id, const QString& pathName);
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
public slots:
private:
    QString m_pathName;
    int iItem;
    QImage mImage;
    int m_width;
    int m_height;
    QBrush m_brush;
};



#endif // CCENTRALBACKGROUNDIMAGE_H
