#include "qtsingleapplication.h"

#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginerroroverview.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtGui/QApplication>
#include <QtGui/QDesktopServices>
#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>



static const char appNameC[] = "Simulator";
static const char corePluginNameC[] = "Core";


typedef QList<ExtensionSystem::PluginSpec *> PluginSpecSet;

// Helpers for displaying messages. Note that there is no console on Windows.
#ifdef Q_OS_WIN
// Format as <pre> HTML
static inline void toHtml(QString &t)
{
    t.replace(QLatin1Char('&'), QLatin1String("&amp;"));
    t.replace(QLatin1Char('<'), QLatin1String("&lt;"));
    t.replace(QLatin1Char('>'), QLatin1String("&gt;"));
    t.insert(0, QLatin1String("<html><pre>"));
    t.append(QLatin1String("</pre></html>"));
}

static void displayHelpText(QString t) // No console on Windows.
{
    toHtml(t);
    QMessageBox::information(0, QLatin1String(appNameC), t);
}

static void displayError(const QString &t) // No console on Windows.
{
    QMessageBox::critical(0, QLatin1String(appNameC), t);
}

#else

static void displayHelpText(const QString &t)
{
    qWarning("%s", qPrintable(t));
}

static void displayError(const QString &t)
{
    qCritical("%s", qPrintable(t));
}

#endif
static inline QString msgCoreLoadFailure(const QString &why)
{
    return QCoreApplication::translate("Application", "Failed to load core: %1").arg(why);
}

static inline int askMsgSendFailed()
{
    return QMessageBox::question(0, QApplication::translate("Application","Could not send message"),
                                 QCoreApplication::translate("Application", "Unable to send command line arguments to the already running instance. "
                                                             "It appears to be not responding. Do you want to start a new instance of Creator?"),
                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Retry,
                                 QMessageBox::Retry);
}

static inline QStringList getPluginPaths()
{
    QStringList rc;
    // Figure out root:  Up one from 'bin'
    QDir rootDir = QApplication::applicationDirPath();
    rootDir.cdUp();
    const QString rootDirPath = rootDir.canonicalPath();
#if !defined(Q_OS_MAC)
    // 1) "plugins" (Win/Linux)
    QString pluginPath = rootDirPath;
    pluginPath += QLatin1Char('/');
    // pluginPath += QLatin1String(IDE_LIBRARY_BASENAME);
    pluginPath += QLatin1String("simulator/plugins");
    rc.push_back(pluginPath);
#else
    // 2) "PlugIns" (OS X)
    QString pluginPath = rootDirPath;
    pluginPath += QLatin1String("/PlugIns");
    rc.push_back(pluginPath);
#endif
    // 3) <localappdata>/plugins/<ideversion>
    //    where <localappdata> is e.g.
    //    <drive>:\Users\<username>\AppData\Local\Nokia\qtcreator on Windows Vista and later
    //    $XDG_DATA_HOME or ~/.local/share/Nokia/qtcreator on Linux
    //    ~/Library/Application Support/Nokia/Qt Creator on Mac
    pluginPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    pluginPath += QLatin1String("/Nokia/");
#if !defined(Q_OS_MAC)
    pluginPath += QLatin1String("simulator");
#else
    pluginPath += QLatin1String("Simulator");
#endif
    pluginPath += QLatin1String("/plugins/");
//    pluginPath += QLatin1String(Core::Constants::IDE_VERSION_LONG);
    rc.push_back(pluginPath);
    return rc;
}

#ifdef Q_OS_MAC
#  define SHARE_PATH "/../Resources"
#else
#  define SHARE_PATH "/../share/simulator"
#endif

int main(int argc, char **argv)
{

    SharedTools::QtSingleApplication app((QLatin1String(appNameC)), argc, argv);
    ExtensionSystem::PluginManager pluginManager;
    pluginManager.setFileExtension(QLatin1String("pluginspec"));
    // pluginManager.setGlobalSettings(globalSettings);
    // pluginManager.setSettings(settings);
    // Load plugins
    const QStringList pluginPaths = getPluginPaths();
    pluginManager.setPluginPaths(pluginPaths);
    
    const PluginSpecSet plugins = pluginManager.plugins();
    ExtensionSystem::PluginSpec *coreplugin = 0;
    foreach (ExtensionSystem::PluginSpec *spec, plugins) {
        if (spec->name() == QLatin1String(corePluginNameC)) {
            coreplugin = spec;
            break;
        }
    }
    if (!coreplugin) {
        QString nativePaths = QDir::toNativeSeparators(pluginPaths.join(QLatin1String(",")));
        const QString reason = QCoreApplication::translate("Application", "Could not find 'Core.pluginspec' in %1").arg(nativePaths);
        displayError(msgCoreLoadFailure(reason));
        return 1;
    }
    if (coreplugin->hasError()) {
        displayError(msgCoreLoadFailure(coreplugin->errorString()));
        return 1;
    }
    const bool isFirstInstance = !app.isRunning();
    if (!isFirstInstance) {
        if (app.sendMessage(pluginManager.serializedArguments()))
            return 0;

        // Message could not be send, maybe it was in the process of quitting
        if (app.isRunning()) {
            // Nah app is still running, ask the user
            int button = askMsgSendFailed();
            while(button == QMessageBox::Retry) {
                if (app.sendMessage(pluginManager.serializedArguments()))
                    return 0;
                if (!app.isRunning()) // App quit while we were trying so start a new creator
                    button = QMessageBox::Yes;
                else
                    button = askMsgSendFailed();
            }
            if (button == QMessageBox::No)
                return -1;
        }
    }

    pluginManager.loadPlugins();
    if (coreplugin->hasError()) {
        displayError(msgCoreLoadFailure(coreplugin->errorString()));
        return 1;
    }
    if (pluginManager.hasError()) {
        ExtensionSystem::PluginErrorOverview errorOverview(&pluginManager);
    }

    if (isFirstInstance) {
        // Set up lock and remote arguments for the first instance only.
        // Silently fallback to unconnected instances for any subsequent instances.
        app.initialize();
        QObject::connect(&app, SIGNAL(messageReceived(QString)),
                        &pluginManager, SLOT(remoteArguments(QString)));
    }
    
    QObject::connect(&app, SIGNAL(fileOpenRequest(QString)), coreplugin->plugin(),
                     SLOT(fileOpenRequest(QString)));
                     
    // shutdown plugin manager on the exit
    QObject::connect(&app, SIGNAL(aboutToQuit()), &pluginManager, SLOT(shutdown()));

    return app.exec();
}
