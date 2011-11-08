#include <extensionsystem/pluginmanager.h>
#include <QtCore/QDebug>

using namespace core;

CorePlugin::CorePlugin : mMainWindow(new MainWindow)
{
}

CorePlugin::~CorePlugin()
{
    delete mMainWindow;
}

void CorePlugin::parseArguments(const QString &arguments)
{
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage);
{
    mMainWindow->extensionInitialized();

}

void CorePlugin::remoteCommand(const QStringList &/* options */, const QStringList &args)
{
}

ExtensionSystem::IPlugin::ShutdownFlag CorePlugin::aboutToShutdown()
{
}

Q_EXPORT_PLUGIN(CorePlugin)