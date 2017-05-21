#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AutoGrid_TimeLine_DataFromFile.h"
#include "autogrid_kline.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // * 显示分时线
//    pgrid = new AutoGrid_TimeLine_DataFromFile(this);
//    pgrid->setObjectName(tr("AutoGrid"));
//    setCentralWidget(pgrid);


    pkline = new AutoGrid_KLine(this);
    pkline->setObjectName(tr("AutoGrid"));
    setCentralWidget(pkline);


    resize(1200,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
