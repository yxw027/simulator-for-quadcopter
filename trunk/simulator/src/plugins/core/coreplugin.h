#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <extensionsystem/iplugin.h>


namespace Core {
namespace Internal {

class MainWindow;

class CorePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT

public:
    CorePlugin();
    ~CorePlugin();

    virtual bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    virtual void extensionsInitialized();
    virtual ShutdownFlag aboutToShutdown();
    virtual void remoteCommand(const QStringList & /* options */, const QStringList &args);

public slots:
    // void fileOpenRequest(const QString&);
//    void helloworld();
private:
    void parseArguments(const QStringList & arguments);
    
    MainWindow *m_mainWindow;
};

} // namespace Internal
} // namespace Core

#endif // COREPLUGIN_H
