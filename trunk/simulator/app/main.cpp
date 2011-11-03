#include <QApplication>
#include <QDesktopWidget>

#include <QDebug>
#include "mainwindow.h"

//#include "SerialThread.h"




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //Window window;
    MainWindow mainWindow;

    //mainWindow.resize(mainWindow.sizeHint());
    mainWindow.show();

    //thread->start();
    //qDebug() << "begin...";
    return app.exec();
}
