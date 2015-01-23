/*  mainwindow.h
 *  This is the header file for mainwindow.cpp, which handles the visual interface
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Client.h"

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
    Ui::MainWindow *ui;


private:


//Functions called by the interface (slots)
private slots:
    void menuExit();
    void connectClient();
};

#endif // MAINWINDOW_H
