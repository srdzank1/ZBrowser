#-------------------------------------------------
#
# Project created by QtCreator 2018-07-02T16:39:29
#
#-------------------------------------------------

QT       += core gui webenginewidgets  webengine concurrent multimedia multimediawidgets network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZBrowser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qhorizontalmenu.cpp \
    simagewidget.cpp \
    cmenuform.cpp \
    XMLParser/cparserxml.cpp \
    clargeimage.cpp \
    VideoFullScreen/fullscreenwindow.cpp \
    VideoFullScreen/fullscreennotification.cpp \
    cheaderimageinfo.cpp \
    cbasewidget.cpp \
    cloaderwidget.cpp \
    ctopbarwidget.cpp \
    Admin/cswitch.cpp \
    Admin/ceditwebsites.cpp \
    ccategorylist.cpp \
    ccategorylistitems.cpp \
    Admin/cschedule.cpp \
    Admin/clargeimageedit.cpp \
    XMLParser/qhelperc.cpp \
    XMLParser/qworker_xml.cpp \
    Admin/cadminsettingswidget.cpp

HEADERS += \
        mainwindow.h \
    qhorizontalmenu.h \
    simagewidget.h \
    cmenuform.h \
    XMLParser/cparserxml.h \
    clargeimage.h \
    VideoFullScreen/fullscreenwindow.h \
    VideoFullScreen/fullscreennotification.h \
    cheaderimageinfo.h \
    cbasewidget.h \
    cloaderwidget.h \
    ctopbarwidget.h \
    Admin/cswitch.h \
    Admin/ceditwebsites.h \
    ccategorylist.h \
    ccategorylistitems.h \
    Admin/cschedule.h \
    Admin/clargeimageedit.h \
    XMLParser/qhelperc.h \
    XMLParser/qworker_xml.h \
    Admin/cadminsettingswidget.h

FORMS += \
        mainwindow.ui \
    qhorizontalmenu.ui \
    cmenuform.ui

RESOURCES += \
    res.qrc




