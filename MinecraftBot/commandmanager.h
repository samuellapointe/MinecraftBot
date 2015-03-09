#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QString>
#include <fstream>

class Client;
class MainWindow;
class CommandManager
{
public:
    //Functions
    CommandManager(Client * client, MainWindow * ui);
    ~CommandManager();
    void readCommand(QString command, QString username);
    void setHome(double x, double y, double z);
    void home(QString username);
    void spawn(QString username);
    //Vars
    QString lastUsername;
    Client * client;
    MainWindow * ui;
    bool waitingForCoords;
};

#endif // COMMANDMANAGER_H
