#ifndef EXTENSIONSYSTEM_PLUGINMANAGER_H
#define EXTENSIONSYSTEM_PLUGINMANAGER_H

#include "extensionsystem_global.h"

#include "pluginspec.h"

#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
class QDir;
QT_END_NAMESPACE

namespace ExtensionSystem {

class EXTENSIONSYSTEM_EXPORT PluginManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PluginManager)

public:
    static PluginManager *instance();

    PluginManager();
    virtual ~PluginManager();

    // Object pool operations
    void addObject(QObject *obj);
    void removeObject(QObject *obj);

    // Plugin operations
    void loadPlugins();
//    void unLoadPlugins();
//    enablePlugins();
//    disablePlugins();
signals:
    void pluginsChanged();
    
public slots:
    void aboutToClose();

private:
    static PluginManager *m_instance;
    void LoadPluginSpec(const QDir& dir);
    QList<PluginSpec> m_pluginSpecs;    
    QStringList m_pluginPaths;
    QString extension;
    QList<QObject *> m_allObjects;    // ### make this a QList<QPointer<QObject> > > ?
};

} // namespace ExtensionSystem

#endif // EXTENSIONSYSTEM_PLUGINMANAGER_H
