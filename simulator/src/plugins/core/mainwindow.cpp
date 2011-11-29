#include "mainwindow.h"
#include "actioncontainer.h"
#include "coreimpl.h"

#include <extensionsystem/pluginmanager.h>
#include <QtGui>
using namespace Core;
using namespace Core::Internal;

MainWindow::MainWindow() :
    EventFilteringMainWindow(),
    m_coreImpl(new CoreImpl(this)),
    m_actionManager(new ActionManagerPrivate(this))
{
    setWindowTitle(tr("Simulator"));
    
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    fileMenu = menuBar()->addMenu(tr("&File"));
}

MainWindow::~MainWindow()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    pm->removeObject(m_coreImpl);
}

bool MainWindow::initialize(QString *errorMessage)
{
    Q_UNUSED(errorMessage)
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    pm->addObject(m_coreImpl);
    return true;
}

void MainWindow::extensionsInitialized()
{
}

void MainWindow::aboutToShutdown()
{
}
