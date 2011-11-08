#ifndef CORE_PLUGIN_H
#define CORE_PLUGIN_H

#include <extensionsystem/iplugin.h>


namespace core {

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
    virtual void remoteCommand(const QStringList &/* options */, const QStringList &args);
    
public:
    void someslot(const QString &);
    
private:
    void parseArguments(const QStringList &argmenuts);
    
    MainWindow *mMainWindow;
};

} // namespace core


#endif // CORE_PLUGIN_H