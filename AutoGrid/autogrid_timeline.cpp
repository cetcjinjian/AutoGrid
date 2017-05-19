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
