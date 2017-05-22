#ifndef AUTOGRID_H
#define AUTOGRID_H

#include <QWidget>



#define COORDINATE_X1       80              //网格距左边距离
#define COORDINATE_Y1       20              //网格距上边距离
#define COORDINATE_X2       80              //网格距右边距离
#define COORDINATE_Y2       20              //网格距下边距离


class AutoGrid : public QWidget
{
    Q_OBJECT
public:
    explicit AutoGrid(QWidget *parent = 0);
    void Initial();
    void DrawBK();
    void DrawGrid();
    void DrawBorder();
    void virtual paintEvent(QPaintEvent* event);
    void virtual resizeEvent(QResizeEvent *event);
    void calGridHeight();
    void calGridWidth();
    void DrawHorLine();
    void DrawVerLine();

public:
    //当前widget宽度和高度
    int m_CurrentHeight;
    int m_CurrentWidth;

    //当前表格宽度和高度
    float m_GridHeight;
    float m_GridWidth;

    //一小格最小高度，当前高度
    float m_atomGridHeight;   
    float m_atomGridHeightMin;

    //一小格最小宽度，当前宽度
    float m_atomGridWidth;  
    float m_atomGridWidthMin;

    //当前小格子数量
    int hgridNum;
    int wgridNum;

    //是否显示水平线和垂直线
    bool isShowHor = true;
    bool isShowVer = true;

signals:

public slots:


};

#endif // AUTOGRID_H
