#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AutoGrid_TimeLine_DataFromFile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    pgrid = new AutoGrid_TimeLine_DataFromFile(this);
    pgrid->setObjectName(tr("AutoGrid"));
    setCentralWidget(pgrid);

    resize(1200,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
