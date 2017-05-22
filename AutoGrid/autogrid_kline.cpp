#include "autogrid_kline.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QKeyEvent>

AutoGrid_KLine::AutoGrid_KLine(QWidget *parent) : QWidget(parent)
{

    DrawBK();
    Initial();
    //开启鼠标追踪
    setMouseTracking(true);
    m_kline.ReadData(tr("dataKLine.txt"));


    //初始化画线的位置
    endPos = m_kline.m_kline.size() -1;
    totalPos = 200;
    if( endPos - totalPos > 0)
        startPos = endPos - totalPos;
}

void AutoGrid_KLine::Initial()
{
    m_atomGridHeight = 50;
    m_atomGridHeightMin = 50;
    m_atomGridWidth = 80;
    m_atomGridWidthMin = 80;
}

void AutoGrid_KLine::DrawBK()
{
    //默认铺满窗口并设置背景色为黑色
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#000000"));
    this->setPalette(palette);
}

void AutoGrid_KLine::DrawGrid()
{
    if(isShowHor)
        DrawHorLine();
    if(isShowVer)
        DrawVerLine();
}


void AutoGrid_KLine::paintEvent(QPaintEvent* event)
{
    calGridHeight();
    calGridWidth();
    DrawGrid();    
    //DrawYTick();
    DrawkLine();
    DrawCrossLine();
}

void AutoGrid_KLine::DrawBorder()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FF0000"));
    painter.setPen(pen);
}

void AutoGrid_KLine::resizeEvent(QResizeEvent *event)
{
    m_CurrentHeight = this->height();
    m_CurrentWidth = this->width();

    m_GridHeight = m_CurrentHeight - COORDINATE_Y1 - COORDINATE_Y2;
    m_GridWidth = m_CurrentWidth - COORDINATE_X1 - COORDINATE_X2;
    //qDebug("%d",m_GridWidth);


}

void AutoGrid_KLine::calGridHeight()
{
    hgridNum = 0;
    int height = m_GridHeight;
    while( height - 2 * m_atomGridHeightMin > 2 * m_atomGridHeightMin)
    {
        hgridNum += 2;
        height -= 2 * m_atomGridHeightMin;
    }
    m_atomGridHeight = m_GridHeight / hgridNum;
}


void AutoGrid_KLine::calGridWidth()
{

    /*
     * 水平网格实现缩放-但同花顺并不使用
    wgridNum = 0;
    int width = m_GridWidth;
    while( width - 2 * m_atomGridWidthMin > 2 * m_atomGridWidthMin)
    {
        wgridNum += 2;
        width -= 2 * m_atomGridWidthMin;
    }
    m_atomGridWidth = m_GridWidth / wgridNum;
    */
    m_atomGridWidth = m_GridWidth / 8;
    wgridNum = 8;
}


void AutoGrid_KLine::DrawHorLine()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FF0000"));
    painter.setPen(pen);

    int xstart = COORDINATE_X1;
    int ystart = COORDINATE_Y1;
    int xend =  m_CurrentWidth - COORDINATE_X2;
    int yend = COORDINATE_Y1;


    if( hgridNum == 0)
    {
        painter.drawLine(xstart,ystart,xend,yend);
        painter.drawLine(xstart,m_CurrentHeight - COORDINATE_Y2,xend,
                         m_CurrentHeight - COORDINATE_Y2);
        return;
    }

    //画水平方向
    for(int i=0;i<hgridNum+1 ;++i)
    {
        if( i == 0 || i == hgridNum)
        {
            pen.setStyle(Qt::SolidLine);
            painter.setPen(pen);
        }
        else
        {
            pen.setStyle(Qt::DashDotLine);
            painter.setPen(pen);
        }
        painter.drawLine(xstart,ystart+i*m_atomGridHeight,
                         xend,yend+i*m_atomGridHeight);
    }


}


void AutoGrid_KLine::DrawVerLine()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FF0000"));
    painter.setPen(pen);

    int xstart = COORDINATE_X1;
    int xend = COORDINATE_X1;
    int ystart = COORDINATE_Y1;
    int yend = m_CurrentHeight - COORDINATE_Y2;

    //画垂直方向
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(xstart,ystart,xend ,yend);
    painter.drawLine(xstart + m_GridWidth,ystart,
                     xend + m_GridWidth ,yend);

}


void AutoGrid_KLine::DrawkLine()
{
    QPainter painter(this);
    QPen     pen;
    QPoint p1;
    QPoint p2;

    xinterLen = (double)m_GridWidth / totalPos;

    m_kline.m_highestBid = 0;
    m_kline.m_lowestBid =10000;
    m_kline.m_totalVolume = 0;

    for(int i = startPos; i< endPos ;++i)
    {
        if(m_kline.m_kline[i].highestBid > m_kline.m_highestBid)
            m_kline.m_highestBid = m_kline.m_kline[i].highestBid;
        if(m_kline.m_kline[i].lowestBid < m_kline.m_lowestBid)
            m_kline.m_lowestBid = m_kline.m_kline[i].lowestBid;
        if(m_kline.m_kline[i].totalVolume > m_kline.m_totalVolume)
           m_kline.m_totalVolume = m_kline.m_kline[i].totalVolume;
    }



    //画Y轴刻度线
    pen.setColor(Qt::red);
    painter.setPen(pen);

    showhighestBid = m_kline.m_highestBid ;
    showlowestBid = m_kline.m_lowestBid  ;
    yinterLen = (showhighestBid - showlowestBid) /hgridNum;
    yscale = m_GridHeight / (showhighestBid - showlowestBid);
    QString str;
    if( hgridNum == 0)
    {
        str.sprintf("%.2f",showlowestBid);
        painter.drawText(QPoint(m_CurrentWidth - COORDINATE_X2 +10,
                                m_CurrentHeight - COORDINATE_Y2),str);
        str.sprintf("%.2f",showhighestBid);
        painter.drawText(QPoint(m_CurrentWidth - COORDINATE_X2 +10,
                                COORDINATE_Y1),str);

        return;
    }
    for(int i=0; i<hgridNum+1;++i)
    {
         str.sprintf("%.2f",showlowestBid+ i*yinterLen);
         painter.drawText(QPoint(m_CurrentWidth-COORDINATE_X2+10,
                                 m_CurrentHeight-COORDINATE_Y2 - i*m_atomGridHeight),
                          str);
    }



    //画k线
    for(int i = startPos; i< endPos ;++i)
    {
        if( m_kline.m_kline[i].openingPrice > m_kline.m_kline[i].closeingPrice)
             pen.setColor(QColor(85,252,252));
        else
            pen.setColor(Qt::red);

        //画最高价与最低价 粗线
        painter.setPen(pen);

        lineWidth = m_GridWidth / totalPos ;
        lineWidth = lineWidth - 0.2*lineWidth;
        if( lineWidth < 3)
            lineWidth = 3;


        //细线
        pen.setWidth(1);
        painter.setPen(pen);
        p1.setX(COORDINATE_X1 + xinterLen*(i - startPos) + 0.5*lineWidth);
        p1.setY( m_CurrentHeight - ( m_kline.m_kline[i].highestBid - showlowestBid)* yscale
                 -COORDINATE_Y2);
        p2.setX(COORDINATE_X1 + xinterLen*(i - startPos) + 0.5*lineWidth);
        p2.setY( m_CurrentHeight - ( m_kline.m_kline[i].lowestBid -  showlowestBid) * yscale
                 -COORDINATE_Y2);
        painter.drawLine(p1,p2);




        //粗线
        pen.setWidth(lineWidth);
        painter.setPen(pen);
        p1.setX(COORDINATE_X1 + xinterLen*(i - startPos) + 0.5*lineWidth);
        p1.setY( m_CurrentHeight -( m_kline.m_kline[i].openingPrice  -showlowestBid)* yscale
                 -COORDINATE_Y2);
        p2.setX(COORDINATE_X1 + xinterLen*(i - startPos) + 0.5*lineWidth);
        p2.setY( m_CurrentHeight -( m_kline.m_kline[i].closeingPrice -showlowestBid)* yscale
                 -COORDINATE_Y2);
        painter.drawLine(p1,p2);
    }
}


void AutoGrid_KLine::DrawXTick()
{


}


void AutoGrid_KLine::DrawYTick()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);

    double showhighestBid = m_kline.m_highestBid;
    double showlowestBid = m_kline.m_lowestBid ;
    //double showhighestBid = 20;
    //double showlowestBid =11;

    yinterLen = (showhighestBid - showlowestBid) /hgridNum;
    yscale = m_GridHeight / (showhighestBid - showlowestBid);


    QString str;
    if( hgridNum == 0)
    {
        str.sprintf("%.2f",showlowestBid);
        painter.drawText(QPoint(m_CurrentWidth - COORDINATE_X2 +10,
                                m_CurrentHeight - COORDINATE_Y2),str);

        str.sprintf("%.2f",showhighestBid);
        painter.drawText(QPoint(m_CurrentWidth - COORDINATE_X2 +10,
                                COORDINATE_Y1),str);

        return;
    }

    for(int i=0; i<hgridNum+1;++i)
    {
         str.sprintf("%.2f",showlowestBid+ i*yinterLen);
         painter.drawText(QPoint(m_CurrentWidth-COORDINATE_X2+10,
                                 m_CurrentHeight-COORDINATE_Y2 - i*m_atomGridHeight),
                          str);
    }

}

void AutoGrid_KLine::DrawCrossLine()
{

//    QLine horLine(COORDINATE_X1,mpoint[count].y(),m_CurrentWidth-COORDINATE_X1,mpoint[count].y());
//    QLine verLine(mpoint[count].x(),COORDINATE_Y1,mpoint[count].x(),m_CurrentHeight-COORDINATE_Y2);
//    QPainter painter(this);
//    QPen     pen;
//    pen.setColor(QColor("#FFFFFF"));
//    pen.setWidth(1);
//    painter.setPen(pen);
//    painter.drawLine(horLine);
//    painter.drawLine(verLine);

    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);





    int x =  double (mousePoint.x() - COORDINATE_X1)/(m_GridWidth) * totalPos;
    x = COORDINATE_X1 + xinterLen * x + 0.5*lineWidth;
    QLine verLine( x,COORDINATE_Y1,x,m_CurrentHeight-COORDINATE_Y2);
    painter.drawLine(verLine);




    int count = (double)(mousePoint.x() - COORDINATE_X1)* totalPos/(m_GridWidth) + startPos;
    int y = ( m_kline.m_kline[count].openingPrice  - showlowestBid )  * yscale;
    QLine horLine(COORDINATE_X1, m_CurrentHeight -COORDINATE_Y2 - y  ,
                  m_CurrentWidth -COORDINATE_X2 ,m_CurrentHeight -COORDINATE_Y2 - y );
    painter.drawLine(horLine);

    //QCursor::setPos(x,mousePoint.y());

}



void AutoGrid_KLine::mouseMoveEvent(QMouseEvent *event)
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



void AutoGrid_KLine::mousePressEvent(QMouseEvent *event)
{

    currentPos = double( event->x() - COORDINATE_X1 ) / m_GridWidth * (endPos -  startPos) + startPos;

    if(event->button() == Qt::LeftButton)
        showCross = !showCross;
    update();
}


void AutoGrid_KLine::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:

        totalPos /= 2;

        if( totalPos < 10)
        {
            totalPos *= 2;
            return;
        }


        endPos = currentPos + totalPos / 2;
        startPos = currentPos - totalPos / 2;

        if( endPos > m_kline.m_kline.size())
        {
             endPos = m_kline.m_kline.size() -1;
             startPos = endPos - totalPos;
        }


        if( startPos < 0)
        {

            startPos = 0;
            endPos = startPos + totalPos;
        }

        if(endPos - totalPos < 0)
        {
            totalPos *= 2;
            return;
        }

         startPos = endPos - totalPos;

        break;
    case Qt::Key_Down:

        totalPos *= 2;


        if( totalPos >  m_kline.m_kline.size())
        {
            totalPos = m_kline.m_kline.size();
            return;
        }


        endPos = currentPos + totalPos / 2;
        startPos = currentPos - totalPos / 2;


        if( endPos > m_kline.m_kline.size())
        {
             endPos = m_kline.m_kline.size() -1;
             startPos = endPos - totalPos;
        }

        if( startPos < 0)
        {

            startPos = 0;
            endPos = startPos + totalPos;
        }


        if(endPos - totalPos < 0)
        {
            totalPos /= 2;
            return;
        }


        startPos = endPos - totalPos;
        break;
    default:
        break;
    }


    update();
}














