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
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(menuExit()));
    //Connect button
    connect(ui->ConnectButton, SIGNAL(released()), this, SLOT(connectClient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//function called by the menu->exit button to close the program
void MainWindow::menuExit()
{
    this->close();
}

//function to validate the connect parameters and launch the client
void MainWindow::connectClient()
{
    writeToConsole("test");
    writeToChat("Test2");
}

//Append text to the console (left)
void MainWindow::writeToConsole(const QString & text)
{
    ui->ConsoleDisplay->append(text);
}

//Append text to the chat (right)
void MainWindow::writeToChat(const QString & text)
{
    ui->ChatDisplay->append(text);
}
