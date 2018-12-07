#include "cschedule.h"

CSchedule::CSchedule(tgroup &data, QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    m_group = data;
    posX = 0;
    posY = 0;
    offset = 125;
    calH = 0;
    calD = 0;
    stepX = 0;
    stepY = 0;

}

CSchedule::~CSchedule()
{

}

void CSchedule::mouseMoveEvent(QMouseEvent *event)
{
    posX = event->pos().x();
    posY = event->pos().y();
}

void CSchedule::mouseReleaseEvent(QMouseEvent * event){
    int s = posX;
    int t = posY;
    for (int i = 0; i < lSchedule.count(); i++){
        tschedulate* item = lSchedule.at(i);
        QRect R(item->rect.x(),
                item->rect.y(),
                item->rect.width() - item->rect.x(),
                item->rect.height() - item->rect.y()
                );

        if (R.contains(s, t)){
            item->stat = !item->stat;
            break;
        }
    }
    repaint();
}

void CSchedule::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPainterPath path;
        path.addRoundedRect(QRectF(0, 0, SchWidth, SchHeight), 10, 10);
        QPen pen(Qt::darkYellow, 10);
        painter.setPen(pen);
        painter.fillPath(path, Qt::white);
        painter.drawPath(path);
        createForm(painter);
        createHoursLabel(painter);
        createWeekLabel(painter);
    painter.end();
}

void CSchedule::menuGlobalSettings(){
    SchWidth = geometry().width();
    SchHeight = geometry().height();
    createScheduleList();
    editSchedule = new QLabel(this);
    editSchedule->setGeometry(20,15, 300, 30);
    QFont cFont;
    cFont.setPointSize(16);
    cFont.setBold(true);
    editSchedule->setFont (cFont);
    editSchedule->setText(QStringLiteral("Edit schedule"));
    CreateCloseOffWidget();
}

void CSchedule::deleteLSch(){
    for (int i = 0; i < lSchedule.count(); i++){
        delete lSchedule.at(i);
    }
    lSchedule.clear();
}


void CSchedule::createScheduleList(){
    deleteLSch();

    calH = SchWidth - 2 * offset;
    calD = SchHeight - 2 * offset;
    stepX = calH / 48;
    stepY = calD / 7;
    for (int d = 0; d < 7; d++){
        for (int h = 0; h < 48; h++){
            tschedulate *item = new tschedulate;
            item->day = d;
            item->hour = h / 2;
            item->min = h % 2 ? 30 : 0;
            QRect r(offset + stepX *h, offset + stepY *d, offset + stepX *(h+1), offset + stepY *(d+1));
            item->rect = r;
            item->stat = false;
            lSchedule.append(item);
        }
    }
}

void CSchedule::createForm(QPainter &painter){
    QPen pen(Qt::darkYellow, 2);
    painter.setPen(pen);

    for (int i = 0; i < lSchedule.count(); i++){
        tschedulate * item = lSchedule.at(i);
        createBasicBlock(painter,
                         item->rect.x(),
                         item->rect.y(),
                         item->rect.width() - item->rect.x(),
                         item->rect.height() - item->rect.y(),
                         item->stat
                         );
    }
}

void CSchedule::createHoursLabel(QPainter &painter){
    QFont cFont;
    cFont.setPointSize(12);
    cFont.setBold(true);
    painter.setFont(cFont);

    QPen pen(Qt::darkYellow, 2);
    painter.setPen(pen);
    for (int h = 0; h < 50; h+=2){
        int hh = h < 26 ? h : h-24;
        if (hh == 0){
            painter.drawText(QPoint(offset + stepX  * h-5 , offset-30), QString::number(12, 10));
        }else if(h == 48){
            painter.drawText(QPoint(offset + stepX * h-5, offset-30), "");
        }else{
            painter.drawText(QPoint(offset + stepX * h-5, offset-30), QString::number(hh/2, 10));
        }
    }

    for (int h = 0; h < 48; h++){
        if (h % 2){
            painter.drawLine(offset + stepX  * h , offset, offset + stepX  * h , offset-5);
        }else{
            painter.drawLine(offset + stepX  * h , offset, offset + stepX  * h , offset-10);
        }
        if (h == 24){
            painter.drawLine(offset + stepX  * h , offset-10, offset + stepX  * h , offset-25);
        }
    }


    cFont.setPointSize(14);
    cFont.setBold(true);
    painter.setFont(cFont);

    painter.drawText(QPoint(offset + stepX * 12 + stepX * 0.8 -5 , offset-50), "AM");
    painter.drawText(QPoint(offset + stepX * 36 + stepX * 0.8 -5, offset-50), "PM");

    cFont.setPointSize(10);
    cFont.setBold(true);
    painter.setFont(cFont);

}




void CSchedule::createWeekLabel(QPainter &painter){
    QPen pen(Qt::darkYellow, 2);
    painter.setPen(pen);
    QString dayName = "s";
    for (int d = 0; d < 7; d++){
        switch (d){
            case 0: dayName = "Monday"; break;
            case 1: dayName = "Tuesday"; break;
            case 2: dayName = "Wednesday"; break;
            case 3: dayName = "Thursday"; break;
            case 4: dayName = "Friday"; break;
            case 5: dayName = "Saturday"; break;
            case 6: dayName = "Sunday"; break;
        }
        painter.drawText(QPoint(20, offset + stepY * d + stepY *0.5), dayName);
    }
}

void CSchedule::createBlockedIntervals(int day, int hours, QPainter &painter){
    QPen pen(Qt::darkYellow, 2);
    painter.setPen(pen);
}


int CSchedule::GetSchedulateDays(){
    return 0;
}

QList<int> CSchedule::GetSchedulateHoursByDay(int day){
    QList<int> a;
    return a;
}

void CSchedule::createBasicBlock(QPainter &painter, const int &x, const int &y, const int &w, const int &h, bool status){
    QPen pen(Qt::darkYellow, 2);
    painter.setPen(pen);

    QPainterPath path;
    path.addRect(QRectF(x, y, w, h));
    painter.setPen(pen);
    if (status){
        painter.fillPath(path, Qt::red);
    }
    painter.drawPath(path);
}

void CSchedule::getFilterSchedule(tfilterschedule &data){
    data.clear();
    for (int i = 0; i < lSchedule.count(); i++){
        tschedulate *item = lSchedule.at(i);
        QString tempItem = QString::number(item->day, 10) + ":"+ QString::number(item->hour,10)+ ":"+ QString::number(item->min,10);
        if (item->stat){
            data.append(tempItem);
        }
    }
}

void CSchedule::setFilterSchedule(tfilterschedule &data){

    QMap<QString, QString> map;
    for(int ia = 0; ia < data.count(); ia++){
        map.insert(data.at(ia), data.at(ia));
    }

    for (int i = 0; i < lSchedule.count(); i++){
        tschedulate *item = lSchedule.at(i);
        QString tempItem = QString::number(item->day, 10) + ":"+ QString::number(item->hour,10)+ ":"+ QString::number(item->min,10);
        if (map[tempItem] == tempItem){
            item->stat = true;
        }
    }

}


void CSchedule::CreateCloseOffWidget(){
    closeOffWidget = new CBaseWidget(this);
    connect(closeOffWidget, SIGNAL(buttonClick()), this, SLOT(ProcCloseWebSites()));
    closeOffWidget->setGeometry(geometry().width() - 54, 6, 48, 48);
    QImage closeOffWidgetTemp = QImage(":/res/image/close_normal.png");
    QImage closeOffWidgetTemp_hover = QImage(":/res/image/close_hover.png");
    QImage closeOffWidgetTemp_click = QImage(":/res/image/close_click.png");
    closeOffWidget->setImage(0, closeOffWidgetTemp, closeOffWidgetTemp_hover, closeOffWidgetTemp_click);
    closeOffWidget->show();
}


void CSchedule::ProcCloseWebSites(){
    emit closeWebSites();
}
