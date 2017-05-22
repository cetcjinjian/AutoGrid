#ifndef AUTOGRID_TIMELINE_DATAFROMFILE_H
#define AUTOGRID_TIMELINE_DATAFROMFILE_H



#include "autogrid_timeline.h"
#include "readdata.h"
#include <QPoint>
#include <vector>

class AutoGrid_TimeLine_DataFromFile : public AutoGrid_TimeLine
{
public:
    explicit AutoGrid_TimeLine_DataFromFile(QWidget *parent = 0);

    ~AutoGrid_TimeLine_DataFromFile();
    void virtual paintEvent(QPaintEvent* event);
    void virtual resizeEvent(QResizeEvent *event);
    void virtual mouseMoveEvent(QMouseEvent* event);
    void virtual mousePressEvent(QMouseEvent* event);
    void virtual keyPressEvent(QKeyEvent* event);
    void DrawYTick();
    void DrawTimeLine();
    void DrawTips();
    void virtual DrawCrossLine();


public:

    ReadData m_data;
    int TEXT_LEN = 50;
    //std::vector<QPoint> mpoint;
    QPoint* mpoint;

};

#endif // AUTOGRID_TIMELINE_DATAFROMFILE_H
