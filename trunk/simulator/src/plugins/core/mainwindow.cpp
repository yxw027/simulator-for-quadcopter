#include "mainwindow.h"

#include <QtGui>
using namespace Core;
using namespace Core::Internal;

MainWindow::MainWindow() :
    EventFilteringMainWindow()
{
    setWindowTitle(tr("Simulator"));
    
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    fileMenu = menuBar()->addMenu(tr("&File"));
}

MainWindow::~MainWindow()
{
}

bool MainWindow::init(QString *errorMessage)
{
    Q_UNUSED(errorMessage)
    //ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    return true;
}

void MainWindow::extensionsInitialized()
{
}

void MainWindow::aboutToShutdown()
{
}
