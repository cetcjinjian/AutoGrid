#include "autogrid_timeline_datafromfile.h"

#include <QPen>
#include <QPainter>
#include <QTime>
#include <QMessageBox>
#include <QKeyEvent>

AutoGrid_TimeLine_DataFromFile::AutoGrid_TimeLine_DataFromFile(QWidget *parent)
                              :AutoGrid_TimeLine(parent)
{
    //mpoint.reserve(500);
    mpoint = new QPoint[250];
    m_data.ReadFSJL();
    m_data.GetFSJLINFO();


}

AutoGrid_TimeLine_DataFromFile::~AutoGrid_TimeLine_DataFromFile()
{
    delete [] mpoint;
    mpoint = nullptr;
}

void AutoGrid_TimeLine_DataFromFile::paintEvent(QPaintEvent *event)
{
    AutoGrid_TimeLine::paintEvent(event);
    //mpoint.clear();
    DrawYTick();
    DrawTimeLine();
    if(showCross)
        DrawTips();
    if(showCross)
        DrawCrossLine();
}


void AutoGrid_TimeLine_DataFromFile::resizeEvent(QResizeEvent *event)
{
    AutoGrid_TimeLine::resizeEvent(event);

}


void AutoGrid_TimeLine_DataFromFile::mouseMoveEvent(QMouseEvent *event)
{
    AutoGrid_TimeLine::mouseMoveEvent(event);
}


void AutoGrid_TimeLine_DataFromFile::DrawYTick()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);


    //画右侧涨跌百分比 0%
    painter.drawText(QPoint(m_CurrentWidth-COORDINATE_X2+10,
                            m_CurrentHeight/2),QString("0.00%"));

    //画左侧初始股票价格 0

    QString str;
    str.sprintf("%.2f",(float)m_data.info.deal_Start / 1000 );
    painter.drawText(QPoint(COORDINATE_X1-TEXT_LEN,
                            m_CurrentHeight/2),str);


    //根据读入的数据画出涨跌百分比和股票价格 先画上半部分
    pen.setColor(Qt::red);
    painter.setPen(pen);
    float Proportional;
    for( int i = hgridNum/2 ; i > 0 ; i-- )
    {
        //画百分比
        Proportional = m_data.info.deal_rate / (hgridNum/2) * i;
        str.sprintf( "%.2f%", Proportional * 100 );
        painter.drawText(QPoint(m_CurrentWidth-COORDINATE_X2+10,
                                m_CurrentHeight/2 - i*m_atomGridHeight),str);

        //画价格
        str.sprintf("%.2f",(float)m_data.info.deal_Start / 1000 * (1+Proportional));
        painter.drawText(QPoint(COORDINATE_X1-TEXT_LEN,
                                m_CurrentHeight/2 - i*m_atomGridHeight),str);
    }


    //画下半部分
    pen.setColor(Qt::green);
    painter.setPen(pen);
    for( int i = hgridNum/2 ; i > 0 ; i-- )
    {
        //画百分比
        Proportional = m_data.info.deal_rate / (hgridNum/2) * i;
        str.sprintf( "%.2f%", -Proportional * 100 );
        painter.drawText(QPoint(m_CurrentWidth-COORDINATE_X2+10,
                                m_CurrentHeight/2 + i*m_atomGridHeight),str);

        //画价格
        str.sprintf("%.2f",(float)m_data.info.deal_Start / 1000 * (1-Proportional));
        painter.drawText(QPoint(COORDINATE_X1-TEXT_LEN,
                                m_CurrentHeight/2 + i*m_atomGridHeight),str);
    }

}

void AutoGrid_TimeLine_DataFromFile::DrawTimeLine()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    float dx = m_GridWidth / 241;
    QPoint p1(COORDINATE_X1,m_CurrentHeight/2);
    QPoint p2(COORDINATE_X1,m_CurrentHeight/2);

    for( int i=0; i < 241; i++ )
    {
        if( 240 == i ){
            p2.setX(m_GridWidth+COORDINATE_X1);
        }
        else
            p2.setX(COORDINATE_X1 + i*dx);
        double rate = float(m_data.fsjl[i].Deal - m_data.info.deal_Start) / m_data.info.deal_Start;
        p2.setY(m_CurrentHeight/2 - rate/m_data.info.deal_rate * (m_GridHeight/2) );
        painter.drawLine(p1,p2);
        mpoint[i] = (p2);
        p1 = p2;
    }
    // mpoint.push_back(p2);
}

void AutoGrid_TimeLine_DataFromFile::DrawTips()
{
    int xlen = mousePoint.x();
    xlen -= COORDINATE_X1;
    int count = ( (double)xlen / m_GridWidth ) * 241;

   // mpoint[count].y();

    //底部时间显示
    QString text;
    double temp = float( mousePoint.x()  - COORDINATE_X1 ) / m_GridWidth ;
    if( temp > 0.5)
        temp += 0.375;
    QDateTime time = QDateTime::fromString("09:30","HH:mm");
    QDateTime newTime;
    newTime = time.addSecs(temp * 60 * 60 * 4);
    text = newTime.toString("HH:mm");

    int iTipsWidth  = 60;
    int iTipsHeight = 20;
    QPainter painter(this);
    QBrush brush(Qt::red);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setBrush(brush);
    painter.setPen(pen);
    QRect rectTime(  mpoint[count].x() - iTipsWidth/2 , m_CurrentHeight  - COORDINATE_Y2 ,
                 iTipsWidth , iTipsHeight);
    painter.drawRect(rectTime);


    QRect rectTimestr(  mpoint[count].x() - iTipsWidth/4, m_CurrentHeight  - COORDINATE_Y2 + iTipsHeight/4 ,
                 iTipsWidth , iTipsHeight);
    painter.drawText(rectTimestr ,text);


    //两侧价格显示

    //左侧
    double yval =  - (  mpoint[count].y() -  m_CurrentHeight/2 ) /(m_GridHeight /2) * m_data.info.deal_rate ;
    yval = m_data.info.deal_Start /1000  * ( 1 + yval );
    QRect rectYval (COORDINATE_X1-iTipsWidth, mpoint[count].y() - iTipsHeight/2,
                    iTipsWidth,iTipsHeight);
    painter.drawRect(rectYval);
    QRect rectYvalstr (COORDINATE_X1-iTipsWidth + iTipsWidth/4, mpoint[count].y() - iTipsHeight/4,
                    iTipsWidth,iTipsHeight);
    painter.drawText(rectYvalstr ,text.sprintf("%.2f",yval));

    //右侧

    double ypec = - (  mpoint[count].y() -  m_CurrentHeight/2 ) /(m_GridHeight /2) * m_data.info.deal_rate ;
    QRect rectYpec (m_CurrentWidth-COORDINATE_X2, mpoint[count].y() - iTipsHeight/2,
                    iTipsWidth,iTipsHeight);
    painter.drawRect(rectYpec);

    QRect rectYstr (m_CurrentWidth-COORDINATE_X2 +iTipsWidth/4 , mpoint[count].y() - iTipsHeight/4,
                    iTipsWidth,iTipsHeight);
    painter.drawText(rectYstr,text.sprintf("%.2f%",ypec*100));

}


void AutoGrid_TimeLine_DataFromFile::mousePressEvent(QMouseEvent *event)
{
    AutoGrid_TimeLine::mousePressEvent(event);
}


void AutoGrid_TimeLine_DataFromFile::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {

    case Qt::Key_Right:
            mousePoint.setX(mousePoint.x() + (double)m_GridWidth/ 241);

            if( mousePoint.x() < COORDINATE_X1 || mousePoint.x() >m_CurrentWidth -  COORDINATE_X2)
                return;

            update();
            break;
    case Qt::Key_Left :

            mousePoint.setX(mousePoint.x() - (double)m_GridWidth/ 241);

            if( mousePoint.x() < COORDINATE_X1 || mousePoint.x() >m_CurrentWidth -  COORDINATE_X2)
                return;

            update();
            break ;
    }
}

void AutoGrid_TimeLine_DataFromFile::DrawCrossLine()
{
    int xlen = mousePoint.x();
    xlen -= COORDINATE_X1;
    int count = ( (double)xlen / m_GridWidth ) * 241;

    QLine horLine(COORDINATE_X1,mpoint[count].y(),m_CurrentWidth-COORDINATE_X1,mpoint[count].y());
    QLine verLine(mpoint[count].x(),COORDINATE_Y1,mpoint[count].x(),m_CurrentHeight-COORDINATE_Y2);
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(horLine);
    painter.drawLine(verLine);
}


