/*  mainwindow.cpp
 *  This class handles the visual interface
 * */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    //Setup the UI, not really sure what this actually does
    ui->setupUi(this);

    //Connext signals to their slots
    //File->Exit to close the program
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(handleButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    this->close();
}
