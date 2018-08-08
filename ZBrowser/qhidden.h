#ifndef QHIDDEN_H
#define QHIDDEN_H

#include <QWidget>

class QHidden : public QWidget
{
    Q_OBJECT
public:
    explicit QHidden(QWidget *parent = 0);
protected:
    void enterEvent(QEvent * event) override;
    void leaveEvent(QEvent * event) override;
signals:
    void showStatus(bool);
public slots:
};

#endif // QHIDDEN_H

