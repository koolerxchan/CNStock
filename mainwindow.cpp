#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showOneDayStockFrame();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showOneDayStockFrame()
{
    ui->oneDaystockFrame->setupStockDate();
    ui->oneDaystockFrame->setupLengend();
}


