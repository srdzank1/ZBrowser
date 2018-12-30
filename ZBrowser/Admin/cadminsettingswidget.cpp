#include "cadminsettingswidget.h"

CAdminSettingsWidget::CAdminSettingsWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    m_settings.KeyboardShortcut = "";
    m_settings.alwaysInFront = true;
    m_settings.enableRestriction = true;
    m_settings.enableSchedule = false;
    m_settings.exitKeyboardShortcut = false;
    m_settings.showCloseButton = false;



    securitySettings = new QLabel(this);
    labelshowCloseButton = new QLabel(this);
    showCloseButton = new CSwitch(this);
    labelalwaysInFront = new QLabel(this);
    alwaysInFront = new CSwitch(this);
    labelexitKeyboardShortcut = new QLabel(this);
    exitKeyboardShortcut = new CSwitch(this);
    labelenableRestriction = new QLabel(this);
    enableRestriction = new CSwitch(this);
    labelkeyboardShortcut = new QLabel(this);
    keyboardShortcut = new QLineEdit(this);
    labelenableSchedule = new QLabel(this);
    enableSchedule = new CSwitch(this);
    buttontWebSites = new QPushButton(this);
    buttonSchedule = new QPushButton(this);
    buttonCloseNow = new QPushButton(this);
    buttonCloseMenu = new QPushButton(this);

    menuGlobalSettings();
    statOn = false;
}

void CAdminSettingsWidget::setSettings(tsettings &esettings){
    m_settings.KeyboardShortcut = esettings.KeyboardShortcut;
    m_settings.alwaysInFront = esettings.alwaysInFront;
    m_settings.enableRestriction = esettings.enableRestriction;
    m_settings.enableSchedule = esettings.enableSchedule;
    m_settings.exitKeyboardShortcut = esettings.exitKeyboardShortcut;
    m_settings.showCloseButton = esettings.showCloseButton;

    keyboardShortcut->setText(m_settings.KeyboardShortcut);
    alwaysInFront->SetStatus(m_settings.alwaysInFront);
    enableRestriction->SetStatus(m_settings.enableRestriction);
    enableSchedule->SetStatus(m_settings.enableSchedule);
    exitKeyboardShortcut->SetStatus(m_settings.exitKeyboardShortcut);
    showCloseButton->SetStatus(m_settings.showCloseButton);
}

void CAdminSettingsWidget::getSettings(tsettings& esettings){
    esettings.KeyboardShortcut = keyboardShortcut->text();
    esettings.alwaysInFront = alwaysInFront->GetStatus();
    esettings.enableRestriction = enableRestriction->GetStatus();
    esettings.enableSchedule = enableSchedule->GetStatus();
    esettings.exitKeyboardShortcut = exitKeyboardShortcut->GetStatus();
    esettings.showCloseButton = showCloseButton->GetStatus();
}


CAdminSettingsWidget::~CAdminSettingsWidget()
{
    delete securitySettings;
    delete labelshowCloseButton;
    delete showCloseButton;
    delete labelalwaysInFront;
    delete alwaysInFront;
    delete labelexitKeyboardShortcut;
    delete exitKeyboardShortcut;
    delete labelenableRestriction;
    delete enableRestriction;
    delete labelkeyboardShortcut;
    delete keyboardShortcut;
    delete labelenableSchedule;
    delete enableSchedule;
    delete buttontWebSites;
    delete buttonSchedule;
    delete buttonCloseNow;
    delete buttonCloseMenu;
}

void CAdminSettingsWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;

        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);

    painter.end();
}

void CAdminSettingsWidget::menuGlobalSettings(){
    securitySettings->setGeometry(20,15, 300, 30);
    QFont cFont;
    cFont.setPointSize(14);
    cFont.setBold(true);
    securitySettings->setFont(cFont);
    securitySettings->setText(QStringLiteral("Security / Settings"));

    //------------------------------------------------
    labelshowCloseButton->setGeometry(20, 100, 200, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelshowCloseButton->setFont(cFont);
    labelshowCloseButton->setText(QStringLiteral("Show close button"));

    showCloseButton->setGeometry( QRect(270 , 100, 100 ,30));
    showCloseButton->SetStatus(m_settings.showCloseButton);
    connect(showCloseButton, SIGNAL(changeSwitchStatus(bool)), this, SLOT(procShowCloseButton(bool)));
    showCloseButton->show();

    //------------------------------------------------
    labelalwaysInFront->setGeometry(20, 140, 200, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelalwaysInFront->setFont(cFont);
    labelalwaysInFront->setText(QStringLiteral("Always in front"));

    alwaysInFront->setGeometry( QRect(270 , 140, 100 ,30));
    alwaysInFront->SetStatus(m_settings.alwaysInFront);
    connect(alwaysInFront, SIGNAL(changeSwitchStatus(bool)), this, SLOT(procShowalwaysInFront(bool)));
    alwaysInFront->show();

    //------------------------------------------------
    labelexitKeyboardShortcut->setGeometry(20, 180, 240, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelexitKeyboardShortcut->setFont(cFont);
    labelexitKeyboardShortcut->setText(QStringLiteral("Exit with keyboard shortcut"));

    exitKeyboardShortcut->setGeometry( QRect(270 , 180, 100 ,30));
    exitKeyboardShortcut->SetStatus(m_settings.exitKeyboardShortcut);
    exitKeyboardShortcut->show();

    //------------------------------------------------
    labelkeyboardShortcut->setGeometry(20, 220, 240, 30);
    cFont.setPointSize(12);
    labelkeyboardShortcut->setFont(cFont);
    labelkeyboardShortcut->setText(QStringLiteral("Keyboard shortcut CTRL+"));


    keyboardShortcut->setGeometry(270, 220, 100, 30);
    cFont.setPointSize(12);
    keyboardShortcut->setMaxLength(1);
    keyboardShortcut->setFont(cFont);
    keyboardShortcut->setText(m_settings.KeyboardShortcut);

    //------------------------------------------------

    labelenableRestriction->setGeometry(20, 260, 240, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelenableRestriction->setFont(cFont);
    labelenableRestriction->setText(QStringLiteral("Enable restrictions"));

    enableRestriction->setGeometry( QRect(270 , 260, 100 ,30));
    enableRestriction->SetStatus(m_settings.enableRestriction);
    connect(enableRestriction, SIGNAL(changeEnableRestriction()), this, SLOT(procShowEnableRestriction()));

    enableRestriction->show();

    //------------------------------------------------

    labelenableSchedule->setGeometry(20, 300, 240, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelenableSchedule->setFont(cFont);
    labelenableSchedule->setText(QStringLiteral("Enable schedule"));

    enableSchedule->setGeometry( QRect(270 , 300, 100 ,30));
    enableSchedule->SetStatus(m_settings.enableSchedule);
    connect(enableSchedule, SIGNAL(changeEnableSchedule()), this, SLOT(procShowEnableSchedule()));
    enableSchedule->show();

    buttontWebSites->setGeometry( QRect(10 , 360, 360 ,55));
    connect(buttontWebSites, SIGNAL(clicked(bool)), this, SLOT(procForEditWebsitesMain(bool)));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttontWebSites->setFont(cFont);
    buttontWebSites->setText(QStringLiteral("Edit web sites"));
    buttontWebSites->show();

    buttonSchedule->setGeometry( QRect(10 , 420, 360 ,55));
    connect(buttonSchedule, SIGNAL(clicked(bool)), this, SLOT(procForScheduleMain(bool)));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttonSchedule->setFont(cFont);
    buttonSchedule->setText(QStringLiteral("Open schedule..."));
    buttonSchedule->show();

    buttonCloseNow->setGeometry( QRect(10 , 480, 360 ,55));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttonCloseNow->setFont(cFont);
    buttonCloseNow->setText(QStringLiteral("Close now!"));
    connect(buttonCloseNow, SIGNAL(clicked(bool)), this, SLOT(procMenuCloseButton(bool)));
    buttonCloseNow->show();

    buttonCloseMenu->setGeometry( QRect(10 , 540, 360 ,55));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttonCloseMenu->setFont(cFont);
    buttonCloseMenu->setText(QStringLiteral("Close menu"));
    connect(buttonCloseMenu, SIGNAL(clicked(bool)), this, SLOT(procMenuClose(bool)));
    buttonCloseMenu->show();
}


void CAdminSettingsWidget::procShowEnableRestriction(){
    emit changeEnableRestriction();
}

void CAdminSettingsWidget::procShowEnableSchedule(){
    emit changeEnableSchedule();
}

void CAdminSettingsWidget::procForEditWebsitesMain(bool){
    emit clickForEditWebsitesMain();
}

void CAdminSettingsWidget::procForScheduleMain(bool){
    emit clickForScheduleMain();
}

void CAdminSettingsWidget::procShowCloseButton(bool stat){
    emit clickForShowCloseButton(stat);
}

void CAdminSettingsWidget::procMenuCloseButton(bool stat){
    emit clickForCloseApplication();
}


void CAdminSettingsWidget::procMenuClose(bool stat){
    emit clickForCloseMenu();
}


void CAdminSettingsWidget::procShowalwaysInFront(bool stat){
    emit changealwaysInFront(stat);
}
