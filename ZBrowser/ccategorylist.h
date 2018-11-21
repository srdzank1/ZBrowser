#ifndef CCATEGORYLIST_H
#define CCATEGORYLIST_H

#include <QWidget>
#include <QList>
#include "XMLParser/cparserxml.h"
#include "Admin/clargeimageeditcategory.h"

typedef QList<QString> tfiltercategory;

class CCategoryList : public QWidget
{
    Q_OBJECT
public:
    explicit CCategoryList(tgroup &data, QWidget *parent = nullptr);
    void createCategoryMenu(int id);
    void getHideStatusCategory(tfiltercategory &mFilterDataCategory);
    void setHideStatusCategory(tfiltercategory &mFilterDataCategory);

protected:
signals:
    void clickForEdit(int &);
    void updateHorizontalMenu();

public slots:
    void processClickForEdit(int&);
    void ProcupdateHorizontalMenu();

private:
    tgroup m_group;
    int m_width;
    int m_height;

    int xOffset;
    int yOffset;
    int mRowCount;
    QList<CLargeImageEditCategory*> pListLargeImage;
    CLargeImageEditCategory * pLargeImage;
};

#endif // CCATEGORYLIST_H
