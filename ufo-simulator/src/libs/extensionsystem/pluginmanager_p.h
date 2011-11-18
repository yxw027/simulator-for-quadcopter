#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

namespace ExtensionSystem {

namespace Internal {


class EXTENSIONSYSTEM_EXPORT PluginManagerPrivate : QObject
{
    Q_OBJECT
public:
    PluginManagerPrivate(PluginManager *pluginManager);
    virtual ~PluginManagerPrivate();

    // Object pool operations
    void addObject(QObject *obj);
    void removeObject(QObject *obj);

    // Plugin operations
    void loadPlugins();
    void aboutToClose();
    void setPluginPaths(const QStringList &paths);

private:
    PluginManager *q;
};

} // namespace Internal
} // namespace ExtensionSystem

#endif // PLUGINMANAGER_P_H
