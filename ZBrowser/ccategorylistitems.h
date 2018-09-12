#ifndef CCATEGORYLISTITEMS_H
#define CCATEGORYLISTITEMS_H

#include <QWidget>
#include <QList>
#include "cparserxml.h"
#include "clargeimageedit.h"

class CCategoryListItems : public QWidget
{
    Q_OBJECT
public:
    explicit CCategoryListItems(tgroup &data, QWidget *parent = nullptr);
    void createCategoryMenuItems(int id);

protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    tgroup m_group;
    int m_width;
    int m_height;

    int xOffset;
    int yOffset;
    int mRowCount;
    QList<CLargeImageEdit*> pListLargeImage;
    CLargeImageEdit * pLargeImage;
};

#endif // CCATEGORYLISTITEMS_H
