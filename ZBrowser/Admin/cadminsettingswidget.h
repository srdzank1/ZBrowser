#ifndef CADMINSETTINGSWIDGET_H
#define CADMINSETTINGSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "cswitch.h"

typedef struct {
   bool  showCloseButton;
   bool  alwaysInFront;
   bool  exitKeyboardShortcut;
   bool  enableRestriction;
   bool  enableSchedule;
   QString  KeyboardShortcut;
} tsettings;


class CAdminSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CAdminSettingsWidget(QWidget *parent = nullptr);
    ~CAdminSettingsWidget();
    void menuGlobalSettings();
    void getSettings(tsettings& esettings);
    void setSettings(tsettings& esettings);
protected:
    void paintEvent(QPaintEvent *event);

signals:
    void clickForEditWebsitesMain();
    void clickForScheduleMain();
    void clickForShowCloseButton(bool);
    void clickForCloseApplication();
    void clickForCloseMenu();
    void changeEnableRestriction();
    void changeEnableSchedule();
    void changealwaysInFront(bool);
public slots:
    void procForEditWebsitesMain(bool);
    void procForScheduleMain(bool);
    void procShowCloseButton(bool);
    void procMenuCloseButton(bool);
    void procMenuClose(bool stat);
    void procShowEnableRestriction();
    void procShowEnableSchedule();
    void procShowalwaysInFront(bool);

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
   tsettings m_settings;
};

#endif // CADMINSETTINGSWIDGET_H
