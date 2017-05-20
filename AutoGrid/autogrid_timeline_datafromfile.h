#ifndef AUTOGRID_TIMELINE_DATAFROMFILE_H
#define AUTOGRID_TIMELINE_DATAFROMFILE_H



#include "autogrid_timeline.h"
#include "readdata.h"

class AutoGrid_TimeLine_DataFromFile : public AutoGrid_TimeLine
{
public:
    explicit AutoGrid_TimeLine_DataFromFile(QWidget *parent = 0);

    void virtual paintEvent(QPaintEvent* event);
    void virtual resizeEvent(QResizeEvent *event);
    void virtual mouseMoveEvent(QMouseEvent* event);
    void virtual mousePressEvent(QMouseEvent* event);
    void DrawYTick();
    void DrawTimeLine();
    void DrawTips();


public:

    ReadData m_data;
    int TEXT_LEN = 50;

};

#endif // AUTOGRID_TIMELINE_DATAFROMFILE_H
