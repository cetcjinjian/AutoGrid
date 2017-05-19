#include "autogrid_timeline_datafromfile.h"

AutoGrid_TimeLine_DataFromFile::AutoGrid_TimeLine_DataFromFile(QWidget *parent)
                              :AutoGrid_TimeLine(parent)
{

}


void AutoGrid_TimeLine_DataFromFile::paintEvent(QPaintEvent *event)
{
    AutoGrid_TimeLine::paintEvent(event);
}


void AutoGrid_TimeLine_DataFromFile::resizeEvent(QResizeEvent *event)
{
    AutoGrid_TimeLine::resizeEvent(event);
}


void AutoGrid_TimeLine_DataFromFile::mouseMoveEvent(QMouseEvent *event)
{
    AutoGrid_TimeLine::mouseMoveEvent(event);
}
