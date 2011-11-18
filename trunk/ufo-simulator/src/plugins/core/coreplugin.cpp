#include "coreplugin.h"
#include "mainwindow.h"

#include <extensionsystem/pluginmanager.h>

#include <QtCore/QtPlugin>
#include <QtCore/QDebug>

using namespace Core;
using namespace Core::Internal;

CorePlugin::CorePlugin() : m_mainWindow(new MainWindow)
{
}

CorePlugin::~CorePlugin()
{
    delete m_mainWindow;
}

void CorePlugin::parseArguments(const QStringList &arguments)
{
    Q_UNUSED(arguments)
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    const bool success = m_mainWindow->initialize(errorMessage);
    if (success) {
    }

    return success;
}

void CorePlugin::extensionsInitialized()
{
//    m_mainWindow->extensionsInitialized();
}

void CorePlugin::remoteCommand(const QStringList &/* options */, const QStringList &args)
{
    m_mainWindow->activateWindow();
}

ExtensionSystem::IPlugin::ShutdownFlag CorePlugin::aboutToShutdown()
{
    m_mainWindow->aboutToShutdown();
}

Q_EXPORT_PLUGIN(CorePlugin)