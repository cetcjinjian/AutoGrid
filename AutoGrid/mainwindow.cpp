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
//    pgrid->setFocusPolicy(Qt::StrongFocus);
//    setCentralWidget(pgrid);


    pkline = new AutoGrid_KLine(this);
    pkline->setObjectName(tr("AutoGrid"));
    pkline->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(pkline);


    resize(1600,1200);
}

MainWindow::~MainWindow()
{
    delete ui;
}
