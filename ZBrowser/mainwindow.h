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



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::MainWindow *ui;
    QHorizontalMenu *customerList;
    CMenuForm *centralMainFormS;
    QWebEngineView *view;
    int height;
    int width;
public slots:
    void processClick(int i);


};

#endif // MAINWINDOW_H
