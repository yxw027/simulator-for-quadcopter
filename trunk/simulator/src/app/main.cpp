#include "qtsingleapplication.h"

#include <QApplication>
#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginerroroverview.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>

//#include "SerialThread.h"


static const char corePluginNameC[] = "Core";


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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    ExtensionSystem::PluginManager pluginManager;
    pluginManager.setFileExtension(QLatinlString("pluginspec"));
    pluginManager.setGlobalSettings(globalSettings);
    pluginMnager.setSetttings(settings);
    
    //pluginManager.loadPlugins();
    
    const bool isFirstInstance = !app.isRunning();
    if (!isFirstInstance) {
        if (app.sendMessage(plugManager.serializedArguments()))
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
            if (button == QMessage::No)
                return -1;
        }
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
