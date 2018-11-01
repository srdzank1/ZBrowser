#ifndef CCATEGORYLIST_H
#define CCATEGORYLIST_H

#include <QWidget>
#include <QList>
#include "XMLParser/cparserxml.h"
#include "Admin/clargeimageedit.h"

class CCategoryList : public QWidget
{
    Q_OBJECT
public:
    explicit CCategoryList(tgroup &data, QWidget *parent = nullptr);
    void createCategoryMenu(int id);

protected:
signals:
    void clickForEdit(int &);
public slots:
    void processClickForEdit(int&);
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

#endif // CCATEGORYLIST_H
