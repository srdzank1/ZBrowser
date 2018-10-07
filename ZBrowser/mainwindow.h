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
#include "cparserxml.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QWebEngineSettings>
#include "fullscreenwindow.h"
#include <QWebEngineFullScreenRequest>
#include <QFuture>
#include <QtConcurrent>
#include <QTextStream>
#include "ccentralbackgroundimage.h"
#include "cheaderimageinfo.h"
#include "cbasewidget.h"
#include <QWebEngineHistory>
#include "qhidden.h"
#include "cloaderwidget.h"
#include <QSound>
#include "ctopbarwidget.h"
#include "cadminsettingswidget.h"
#include "ceditwebsites.h"
#include "cschedule.h"
#include <QDesktopServices>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

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

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyReleaseEvent(QKeyEvent *);
private:
    Ui::MainWindow *ui;
    QHorizontalMenu *horizontalMenu;
    CMenuForm *centralMenu;
    QWebEngineView *view;
    QWebEngineView *viewUrl;
    QWebEngineView *viewInit;


    int height;
    int width;
    QScopedPointer<FullScreenWindow> m_fullScreenWindow;
    CParserXML *parser;
    QScrollArea *scroll;
    CCentralBackgroundImage *backgroundImage;
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
    QHidden *hiddenWidget;
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

public slots:
    void processClick(int i);
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
    void ProcForwardViewClick();
    void procLoadUrlChanged(const QUrl&);
    void ProcShowHMenu(bool s);
    void procSelectionChanged();
    void ProcAdminClick();
    void procEditWebsites();
    void procEditSchedule();

};

#endif // MAINWINDOW_H
