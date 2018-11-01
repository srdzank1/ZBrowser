#include "cadminsettingswidget.h"

CAdminSettingsWidget::CAdminSettingsWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    menuGlobalSettings();
    statOn = false;
}

CAdminSettingsWidget::~CAdminSettingsWidget()
{

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


    securitySettings = new QLabel(this);
    securitySettings->setGeometry(20,15, 300, 30);
    QFont cFont;
    cFont.setPointSize(14);
    cFont.setBold(true);
    securitySettings->setFont(cFont);
    securitySettings->setText(QStringLiteral("Security / Settings"));

    //------------------------------------------------
    labelshowCloseButton = new QLabel(this);
    labelshowCloseButton->setGeometry(20, 100, 200, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelshowCloseButton->setFont(cFont);
    labelshowCloseButton->setText(QStringLiteral("Show close button"));

    showCloseButton = new CSwitch(this);
    showCloseButton->setGeometry( QRect(270 , 100, 100 ,30));
    showCloseButton->show();

    //------------------------------------------------
    labelalwaysInFront = new QLabel(this);
    labelalwaysInFront->setGeometry(20, 140, 200, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelalwaysInFront->setFont(cFont);
    labelalwaysInFront->setText(QStringLiteral("Always in front"));

    alwaysInFront = new CSwitch(this);
    alwaysInFront->setGeometry( QRect(270 , 140, 100 ,30));
    alwaysInFront->show();

    //------------------------------------------------
    labelexitKeyboardShortcut = new QLabel(this);
    labelexitKeyboardShortcut->setGeometry(20, 180, 240, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelexitKeyboardShortcut->setFont(cFont);
    labelexitKeyboardShortcut->setText(QStringLiteral("Exit with keyboard shortcut"));

    exitKeyboardShortcut = new CSwitch(this);
    exitKeyboardShortcut->setGeometry( QRect(270 , 180, 100 ,30));
    exitKeyboardShortcut->show();

    //------------------------------------------------
    labelenableRestriction = new QLabel(this);
    labelenableRestriction->setGeometry(20, 220, 240, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelenableRestriction->setFont(cFont);
    labelenableRestriction->setText(QStringLiteral("Enable restrictions"));

    enableRestriction = new CSwitch(this);
    enableRestriction->setGeometry( QRect(270 , 220, 100 ,30));
    enableRestriction->show();

    //------------------------------------------------
    labelkeyboardShortcut = new QLabel(this);
    labelkeyboardShortcut->setGeometry(20, 260, 240, 30);
    cFont.setPointSize(12);
    labelkeyboardShortcut->setFont(cFont);
    labelkeyboardShortcut->setText(QStringLiteral("Keyboard shortcut CTRL+"));


    keyboardShortcut = new QLineEdit(this);
    keyboardShortcut->setGeometry(270, 260, 100, 30);
    cFont.setPointSize(12);
    keyboardShortcut->setMaxLength(1);
    keyboardShortcut->setFont(cFont);
    keyboardShortcut->setText(QStringLiteral("L"));

    //------------------------------------------------

    labelenableSchedule = new QLabel(this);
    labelenableSchedule->setGeometry(20, 300, 240, 30);
    cFont.setPointSize(12);
    cFont.setBold(false);
    labelenableSchedule->setFont(cFont);
    labelenableSchedule->setText(QStringLiteral("Enable schedule"));

    enableSchedule = new CSwitch(this);
    enableSchedule->setGeometry( QRect(270 , 300, 100 ,30));
    enableSchedule->show();


    //------------------------------------------------

    buttontWebSites = new QPushButton(this);
    buttontWebSites->setGeometry( QRect(10 , 360, 360 ,55));
    connect(buttontWebSites, SIGNAL(clicked(bool)), this, SLOT(procForEditWebsitesMain(bool)));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttontWebSites->setFont(cFont);
    buttontWebSites->setText(QStringLiteral("Edit web sites"));
    buttontWebSites->show();

    buttonSchedule = new QPushButton(this);
    buttonSchedule->setGeometry( QRect(10 , 420, 360 ,55));
    connect(buttonSchedule, SIGNAL(clicked(bool)), this, SLOT(procForScheduleMain(bool)));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttonSchedule->setFont(cFont);
    buttonSchedule->setText(QStringLiteral("Open schedule..."));
    buttonSchedule->show();

    buttonCloseNow = new QPushButton(this);
    buttonCloseNow->setGeometry( QRect(10 , 480, 360 ,55));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttonCloseNow->setFont(cFont);
    buttonCloseNow->setText(QStringLiteral("Close now!"));
    buttonCloseNow->show();


    buttonCloseMenu = new QPushButton(this);
    buttonCloseMenu->setGeometry( QRect(10 , 540, 360 ,55));
    cFont.setPointSize(12);
    cFont.setBold(true);
    buttonCloseMenu->setFont(cFont);
    buttonCloseMenu->setText(QStringLiteral("Close menu"));
    buttonCloseMenu->show();

}

void CAdminSettingsWidget::procForEditWebsitesMain(bool){
    emit clickForEditWebsitesMain();
}

void CAdminSettingsWidget::procForScheduleMain(bool){
    emit clickForScheduleMain();
}

