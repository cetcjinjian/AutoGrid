#ifndef AUTOGRID_TIMELINE_DATAFROMFILE_H
#define AUTOGRID_TIMELINE_DATAFROMFILE_H



#include "autogrid_timeline.h"

class AutoGrid_TimeLine_DataFromFile : public AutoGrid_TimeLine
{
public:
    explicit AutoGrid_TimeLine_DataFromFile(QWidget *parent = 0);

    void virtual paintEvent(QPaintEvent* event);
    void virtual resizeEvent(QResizeEvent *event);
    void virtual mouseMoveEvent(QMouseEvent* event);

};

#endif // AUTOGRID_TIMELINE_DATAFROMFILE_H
