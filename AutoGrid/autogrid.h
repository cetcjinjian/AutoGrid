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
    void DrawBK();
    void DrawGrid();
    void DrawBorder();
    void virtual paintEvent(QPaintEvent* event);
    void virtual resizeEvent(QResizeEvent *event);

private:
    int m_CurrentHeight;
    int m_CurrentWidth;

    float m_GridHeight;
    float m_GridWidth;

signals:

public slots:
};

#endif // AUTOGRID_H
