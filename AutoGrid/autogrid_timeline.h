#ifndef AUTOGRID_TIMELINE_H
#define AUTOGRID_TIMELINE_H


#include "autogrid.h"

class AutoGrid_TimeLine : public AutoGrid
{
public:
    explicit AutoGrid_TimeLine(QWidget *parent = 0);

    void DrawXTick();
    void DrawYTick();

    void virtual paintEvent(QPaintEvent* event);
    void virtual resizeEvent(QResizeEvent *event);
};

#endif // AUTOGRID_TIMELINE_H
