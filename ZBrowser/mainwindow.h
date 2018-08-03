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
    int height;
    int width;
    QScopedPointer<FullScreenWindow> m_fullScreenWindow;
    CParserXML *parser;
    QScrollArea *scroll;
    CCentralBackgroundImage *backgroundImage;
    CHeaderImageInfo *headerImageInfo;
    CBaseWidget * upArrowWidget;
    CBaseWidget * downArrowWidget;
    QString cont;
public slots:
    void processClick(int i);
    void ProcClickForUrl(QString &i);
    void fullScreenRequested(QWebEngineFullScreenRequest request);
    void procLoadUrlFinished(bool s);
    void ProcUpClick();
    void ProcDownClick();
};

#endif // MAINWINDOW_H
