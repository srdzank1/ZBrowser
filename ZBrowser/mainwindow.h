#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QListWidget>
#include <QWebEngineView>
#include <QSplitter>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QMenu>
#include "qhorizontalmenu.h"
#include "cmenuform.h"
#include "XMLParser/cparserxml.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QWebEngineSettings>
#include "VideoFullScreen/fullscreenwindow.h"
#include <QWebEngineFullScreenRequest>
#include <QFuture>
#include <QtConcurrent>
#include <QTextStream>

#include "cheaderimageinfo.h"
#include "cbasewidget.h"
#include <QWebEngineHistory>
#include "cloaderwidget.h"
#include <QSound>
#include "ctopbarwidget.h"
#include "Admin/cadminsettingswidget.h"
#include "Admin/ceditwebsites.h"
#include "Admin/cschedule.h"
#include <QDesktopServices>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include "XMLParser/qhelperc.h"
#include <QDir>
#include "ccategorylistitems.h"
#include <QMap>
#include <QStandardPaths>

#define SUBDIR "/images/"
//#define SUBDIR "/"

class QWebView;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initVideo();
    void LoadXMLFileFromURLInit();
    void CreateInitElement();
    void SaveSettingData();
    void ReadSettingData();
    void SaveFilteredData();
    void ReadFilteredData();
    void clearXMLData();
    void InitXMLGrabber();
    void SaveFilteredDataCategory();
    void ReadFilteredDataCategory();
    void SaveFilteredDataSchedule();
    void ReadFilteredDataSchedule();
    void ZackClock();


protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyReleaseEvent(QKeyEvent *);
private:
    Ui::MainWindow *ui;
    QHorizontalMenu *horizontalMenu;
    CMenuForm *centralMenu;
    QWebEngineView *view;
    QWebEngineView *viewInit;
    QTimer *autoTimer;

    void createView();
    void createViewInit();
    void CreateAdminWidget();
    void CreateHeaderImageInfoCategory(tgroup &xmlData);
    void CreateCloseOffWidget();
    void CreateHomeWidget();
    void CreateForwardWidget();
    void CreateBackArrowWidget();
    void CreateDownArrowWidget();
    void CreateUpArrowWidget();
    void CreateCentralMenuScrollArea(tgroup &xmlData);
    void CreateHorizontalMenu(tgroup &xmlData);
    void CreateHeaderImageInfo(tgroup &xmlData);
    void CreateTopBarWidget();
    void CreateLoader();
    QStringList GetAllImagesInFolder();
    bool ItemImageExist(QStringList &images, QString & item);
    QString ParseTransform(QString url);



    int height;
    int width;
    QScopedPointer<FullScreenWindow> m_fullScreenWindow;
    CParserXML *parser;
    QScrollArea *scroll;
    CHeaderImageInfo *headerImageInfo;
    CHeaderImageInfo *headerImageInfoCategory;

    CBaseWidget * upArrowWidget;
    CBaseWidget * downArrowWidget;
    QString cont;
    QString cont2;

    CBaseWidget * homeWidget;
    CBaseWidget * backWidget;
    CBaseWidget * forwardWidget;
    CBaseWidget * closeOffWidget;
    CBaseWidget * adminWidget;
    bool statusHistoryEnabled;
    QString m_url;
    int resizeCount;
    int catIndx;
    CLoaderWidget *loader;
    CTopBarWidget *topBarWidget;
    CAdminSettingsWidget * admin;
    CEditWebSites *editWebSites;
    CSchedule * editSchedule;

    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QTimer *t;
    QTimer *t2;
    QTimer *t5;
    bool checkProc;
    tgroup xmlData ;
    tgroup xmlDataOrig;
    tsettings mSettings;
    tfilterwebsite mFilteredWeb;
    tfiltercategory mFilteredCategory;
    tfilterschedule mFilteredSchedule;

public slots:
    void processClick(int i);
    void processClickInit(int i);
    void ProcClickForUrl(QString &i, QString&t, QImage& image );
    void fullScreenRequested(QWebEngineFullScreenRequest request);
    void procLoadUrlFinished(bool s);
    void procStartedUrlFinished();
    void procLoadProgress(int);
    void TimerFinish();
    void TimerFinish2();
    void TimerFinish5();
    void ProcUpClick();
    void ProcDownClick();
    void ProcHomeClick();
    void ProcBackViewClick();
    void ProcCloseOffClick();
    void ProcCloseApplication();
    void ProcForwardViewClick();
    void procLoadUrlChanged(const QUrl&);
    void ProcShowHMenu(bool s);
    void procSelectionChanged();
    void ProcAdminClick();
    void procEditWebsites();
    void procEditSchedule();
    void ProcShowCloseButton(bool);
    void procWebSitesChangeCategory(int&i);
    void ProcCloseAdminMenu();
    void procCloseWebSites();
    void UpdateXMLFromWeb();
    void procupdateHorizMenu();
    void updateTimer();
    void ProcChangeEnableRestriction();
    void ProcChangeEnableSchedule();
};

#endif // MAINWINDOW_H
