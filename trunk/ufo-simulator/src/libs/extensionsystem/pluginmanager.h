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
signals:

public slots:
    void aboutToClose();

private:
    QList<PluginSpec> m_specs;
    QList<QObject* > m_objList;

    void LoadPluginSpec(const QDir& dir);
};

} // namespace ExtensionSystem

#endif // EXTENSIONSYSTEM_PLUGINMANAGER_H
