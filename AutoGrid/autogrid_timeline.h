#ifndef AUTOGRID_TIMELINE_H
#define AUTOGRID_TIMELINE_H


#include "autogrid.h"
#include <QMouseEvent>
class AutoGrid_TimeLine : public AutoGrid
{
public:
    explicit AutoGrid_TimeLine(QWidget *parent = 0);

    void DrawXTick();
    void DrawYTick();
    void virtual DrawCrossLine();

    void virtual paintEvent(QPaintEvent* event);
    void virtual resizeEvent(QResizeEvent *event);
    void virtual mouseMoveEvent(QMouseEvent* event);
    void virtual mousePressEvent(QMouseEvent* event);


public:
    QPoint mousePoint ;
    bool showCross = false;
};

#endif // AUTOGRID_TIMELINE_H
