#include "commandmanager.h"
#include "Client.h"

CommandManager::CommandManager(Client * c, MainWindow * i_ui)
{
    client = c;
    ui = i_ui;
    waitingForCoords = false;
}

CommandManager::~CommandManager()
{

}

void CommandManager::readCommand(QString command, QString username)
{
    QStringList args = command.split(' ');
    if(args[0].toLower().compare("!sethome") == 0)
    {
        client->sendMessage("/tp "+username);
        waitingForCoords = true;
        lastUsername = username;
        //From there, we wait to get the coords to set the home
    }
    else if(args[0].toLower().compare("!home") == 0)
    {
        lastUsername = username;
        home();
    }
    else
    {
        client->sendMessage("Command not recognized! ");
    }
}

void CommandManager::setHome(double x, double y, double z)
{
    waitingForCoords = false;
    client->sendMessage("Setting home for " + lastUsername + " at coords " + QString::number(x) + "," + QString::number(y) + "," + QString::number(z));

    std::fstream homeFile;
    std::vector<QString> homes;
    homeFile.open("homes_" + client->ip.toStdString() + ".txt", std::ios::in);
    string line;

    bool playerFound = false;
    while(getline(homeFile, line))
    {
        QString qline = QString::fromStdString(line).simplified();
        QStringList qlines = qline.split(' ');
        if(qlines.at(0).compare(lastUsername) == 0)
        {//Update home for the player
            playerFound = true;
            homes.push_back(lastUsername + " " + QString::number(x) + " " + QString::number(y) + " " + QString::number(z));
        }
        else
        {
            homes.push_back(qline);
        }

    }
    if(!playerFound)
    {
        homes.push_back(lastUsername + " " + QString::number(x) + " " + QString::number(y) + " " + QString::number(z));
    }
    homeFile.close();

    //Write the file back
    homeFile.open("homes_" + client->ip.toStdString() + ".txt", std::ios::out);
    for(int i = 0; i < homes.size(); i++)
    {
        homeFile << homes[i].toStdString() << std::endl;
    }
    homeFile.close();
}

void CommandManager::home()
{
    std::fstream homeFile;
    homeFile.open("homes_" + client->ip.toStdString() + ".txt", std::ios::in);
    string line;

    bool playerFound = false;
    while(getline(homeFile, line))
    {
        QString qline = QString::fromStdString(line).simplified();
        QStringList qlines = qline.split(' ');
        if(qlines.at(0).compare(lastUsername) == 0)
        {//Update home for the player
            playerFound = true;
            client->sendMessage("/tp "+qline);
            client->sendMessage("Done!");
        }
    }
    if(!playerFound)
    {
        client->sendMessage("No home found for user "+lastUsername);
    }
    homeFile.close();
}
