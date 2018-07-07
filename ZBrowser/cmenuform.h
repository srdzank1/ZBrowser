#ifndef CMENUFORM_H
#define CMENUFORM_H

#include <QWidget>
#include "simagewidget.h"

namespace Ui {
class CMenuForm;
}

class CMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit CMenuForm(QWidget *parent = 0);
    ~CMenuForm();
    void UpdateD(QRect r);
protected:
    virtual bool event(QEvent *event);
public slots:
    void processClick(int i);
private:
    Ui::CMenuForm *ui;
    SImageWidget *label[5][5];
};

#endif // CMENUFORM_H
