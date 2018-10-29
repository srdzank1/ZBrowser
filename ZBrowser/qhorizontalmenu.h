#ifndef QHORIZONTALMENU_H
#define QHORIZONTALMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "simagewidget.h"
#include "cparserxml.h"
#include <QDir>
#define SUBDIR "/images/"
//#define SUBDIR "/"

namespace Ui {
class QHorizontalMenu;
}

class QHorizontalMenu : public QWidget
{
    Q_OBJECT

public:
    explicit QHorizontalMenu(QWidget *parent , tgroup &data );
    ~QHorizontalMenu();
    void UpdateD(QRect r);
    void setParsedData(tgroup &data){m_group = data;}

private:
    Ui::QHorizontalMenu *ui;
    QHBoxLayout *hlayout;
    SImageWidget *imageItem[20];
    tgroup m_group;
    int catwegoryCount;

public slots:
    void processClick(int i);
signals:
    void click(int);
};

#endif // QHORIZONTALMENU_H
