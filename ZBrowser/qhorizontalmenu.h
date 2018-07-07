#ifndef QHORIZONTALMENU_H
#define QHORIZONTALMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "simagewidget.h"


namespace Ui {
class QHorizontalMenu;
}

class QHorizontalMenu : public QWidget
{
    Q_OBJECT

public:
    explicit QHorizontalMenu(QWidget *parent = 0);
    ~QHorizontalMenu();
    void UpdateD(QRect r);

private:
    Ui::QHorizontalMenu *ui;
    QHBoxLayout *hlayout;
    SImageWidget *label[10];

public slots:
    void processClick(int i);
signals:
    void click(int);
};

#endif // QHORIZONTALMENU_H
