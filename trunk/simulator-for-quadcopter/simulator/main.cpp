#include <QApplication>
#include <QDesktopWidget>


#include "SerialThread.h"



#include "window.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;


    //window.resize(window.sizeHint());
    window.showMaximized();

    //thread->start();

    return app.exec();
}
