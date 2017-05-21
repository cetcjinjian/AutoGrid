#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "autogrid.h"
#include "autogrid_kline.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AutoGrid* pgrid;
    AutoGrid_KLine* pkline;
};

#endif // MAINWINDOW_H
