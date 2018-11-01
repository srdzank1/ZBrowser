#ifndef CCATEGORYLISTITEMS_H
#define CCATEGORYLISTITEMS_H

#include <QWidget>
#include <QList>
#include "XMLParser/cparserxml.h"
#include "Admin/clargeimageedit.h"

class CCategoryListItems : public QWidget
{
    Q_OBJECT
public:
    explicit CCategoryListItems(tgroup &data, QWidget *parent = nullptr);
    void createCategoryMenuItems(int id);

protected:
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
