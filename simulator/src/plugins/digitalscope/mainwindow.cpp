#include "mainwindow.h"

#include <QMenuBar>


MainWindow::MainWindow()
{
    setWindowTitle(tr("Simulator"));
    
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    fileMenu = menuBar()->addMenu(tr("&File"));
}

MainWindow::~MainWindow()
{
}
