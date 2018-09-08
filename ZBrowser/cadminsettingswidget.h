#ifndef CADMINSETTINGSWIDGET_H
#define CADMINSETTINGSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "cswitch.h"

class CAdminSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CAdminSettingsWidget(QWidget *parent = nullptr);
    ~CAdminSettingsWidget();
    void menuGlobalSettings();
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
private:
    bool statOn;
   QLabel *securitySettings;
   QLabel *editWebSites;
   QLabel *openSchedule;
   QLabel *CloseNow;
   QLabel *CloseMenu;

   QLabel *labelshowCloseButton;
   CSwitch *showCloseButton;
   QLabel *labelalwaysInFront;
   CSwitch *alwaysInFront;
   QLabel *labelexitKeyboardShortcut;
   CSwitch *exitKeyboardShortcut;

   QLabel *labelenableRestriction;
   CSwitch *enableRestriction;

   QLabel *labelkeyboardShortcut;
   QLineEdit *keyboardShortcut;

   QLabel *labelenableSchedule;
   CSwitch *enableSchedule;
   QPushButton * buttontWebSites;
   QPushButton * buttonSchedule;
   QPushButton * buttonCloseNow;
   QPushButton * buttonCloseMenu;
};

#endif // CADMINSETTINGSWIDGET_H
