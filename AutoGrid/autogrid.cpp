#include "autogrid.h"

#include <QPainter>
#include <QPen>

AutoGrid::AutoGrid(QWidget *parent) : QWidget(parent)
{
    DrawBK();
}


void AutoGrid::DrawBK()
{
    //默认铺满窗口并设置背景色为黑色
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#000000"));
    this->setPalette(palette);
}


void AutoGrid::DrawGrid()
{


}


void AutoGrid::paintEvent(QPaintEvent* event)
{
    DrawGrid();
}

void AutoGrid::DrawBorder()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FF0000"));
    painter.setPen(pen);


}

void AutoGrid::resizeEvent(QResizeEvent *event)
{
    m_CurrentHeight = this->height();
    m_CurrentHeight = this->width();
}



















