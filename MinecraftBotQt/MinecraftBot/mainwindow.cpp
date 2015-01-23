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
    bool validated = true;

    //Grab data from the text boxes
    QString &username = ui->UsernameInput->text();
    QString &password = ui->PasswordInput->text();
    QString &ip = ui->IPInput->text();
    QString &portString = ui->PortInput->text();
    short port;

    //Validate it
    if(username.length() == 0)
    {
        writeToConsole("The username field is empty!");
        validated = false;
    }
    if(password.length() == 0)
    {
        writeToConsole("The password field is empty!");
        validated = false;
    }
    if(ip.length() == 0)
    {
        writeToConsole("The IP address field is empty!");
        validated = false;
    }
    if(portString.length() == 0)
    {
        writeToConsole("The server port field is empty!");
        validated = false;
    }
    else
    {
        bool conversionAccepted;
        port = portString.toShort(&conversionAccepted, 10);
        if(!conversionAccepted)
        {
            writeToConsole("The port must be a number!");
            validated = false;
        }
    }

    if(validated)
    {
        //I convert QStrings to STD strings before sending it to the client
        Client * client = new Client(this, username.toStdString(), password.toStdString(), ip.toStdString(), port);
    }
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
