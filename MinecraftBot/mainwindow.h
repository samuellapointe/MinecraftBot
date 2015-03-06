/*  mainwindow.h
 *  This is the header file for mainwindow.cpp, which handles the visual interface
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Client.h"
#include "packet.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeToConsole(const QString &text); //Append to the left console
    void writeToChat(const QString &text); //Append to the right console
    void displayPacket(const bool received, const int id, const int size, const QColor &color = QColor(255,255,255), const QString &info = "none");
    bool showUnknownPackets();
    bool autoReconnect();
    Ui::MainWindow *ui;


private:
    Client * client;

//Functions called by the interface (slots)
private slots:
    void menuExit();
    void sendMessage();
public slots:
    void connectClient();
};

#endif // MAINWINDOW_H
