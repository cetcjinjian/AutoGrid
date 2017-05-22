#include "autogrid_timeline.h"
#include <QPen>
#include <QPainter>
#include <QTime>

AutoGrid_TimeLine::AutoGrid_TimeLine(QWidget *parent):
                   AutoGrid(parent)
{

}


void AutoGrid_TimeLine::paintEvent(QPaintEvent* event)
{
    AutoGrid::paintEvent(event);
    DrawXTick();
//    if(showCross)
//        DrawCrossLine();
}


void AutoGrid_TimeLine::resizeEvent(QResizeEvent* event)
{
    AutoGrid::resizeEvent(event);
}


void AutoGrid_TimeLine::DrawXTick()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    for(int i=0;i<wgridNum+1;++i)
    {
        double px =  COORDINATE_X1 - 10 + i * m_atomGridWidth;
        double py =  m_CurrentHeight - COORDINATE_Y2 + 10;
        QDateTime time = QDateTime::fromString("09:30","HH:mm");
        QDateTime newTime;
        if(i >=4){
           newTime = time.addSecs(1800*(i+3));
        }else if(i<4){
           newTime = time.addSecs(1800*i);
        }
        QString str = newTime.toString("HH:mm");
        painter.drawText(px,py,str);
    }
}


void AutoGrid_TimeLine::mouseMoveEvent(QMouseEvent* event)
{
    mousePoint = QPoint(event->pos());
    float xmin = COORDINATE_X1;
    float xmax = m_CurrentWidth - COORDINATE_X2;
    float ymin = COORDINATE_Y1;
    float ymax = m_CurrentHeight - COORDINATE_Y2;

    if(mousePoint.y() < ymin || mousePoint.y() > ymax){
        return;
    }
    if(mousePoint.x() < xmin || mousePoint.x() > xmax){
        return;
    }
    update();
}

void AutoGrid_TimeLine::DrawCrossLine()
{
    QLine horLine(COORDINATE_X1,mousePoint.y(),m_CurrentWidth-COORDINATE_X1,mousePoint.y());
    QLine verLine(mousePoint.x(),COORDINATE_Y1,mousePoint.x(),m_CurrentHeight-COORDINATE_Y2);
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(horLine);
    painter.drawLine(verLine);
}

void AutoGrid_TimeLine::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
        showCross = !showCross;
    update();
}
