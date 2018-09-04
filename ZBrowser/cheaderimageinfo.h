#ifndef CHEADERIMAGEINFO_H
#define CHEADERIMAGEINFO_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class CHeaderImageInfo : public QWidget
{
    Q_OBJECT
public:
    explicit CHeaderImageInfo(QWidget *parent = nullptr);
    ~CHeaderImageInfo();

    void setImagePathName(int id, const QString& pathName);
    void setImage(int id, QImage & img );
    QImage getImage(){return mImage;}
    void setWidth(int w){m_width = w;}
    void setHeight(int h){m_height = h;}
    void setTitleIcon(const QString& name);
    void setAnimate(bool stat ){mAnimate = stat;}



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
    bool mAnimate;
    bool onEnter;
};

#endif // CHEADERIMAGEINFO_H
