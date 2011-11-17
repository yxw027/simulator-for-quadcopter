#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "extensionsystem_global.h"

#include <QtCore/QObject>

namespace ExtensionSystem {

class PluginSpec;
class QList;

class EXTENSIONSYSTEM_EXPORT IPlugin : public QObject
{
    Q_OBJECT

public:
    enum ShutdownFlag {
        SynchronousShutdown,
        AsynchronousShutdown
    };

    IPlugin();
    virtual ~IPlugin();

    virtual bool initialize(const QStringList &arguments, QString *errorString) = 0;
    virtual void extensionsInitialized() = 0;
    virtual ShutdownFlag aboutToShutdown();

    PluginSpec *pluginSpec() const;

    void addObject(QObject *obj);
    void addAutoReleasedObject(QObject *obj);
    void removeObject(QObject *obj);

signals:
    void asynchronousShutdownFinished();

private:
    void setSpec(const PluginSpec * ptr);
    const PluginSpec * m_spec;
    QList<QObject*> m_objList;

    friend class PluginManager;
};

} // namespace ExtensionSystem

#endif // IPLUGIN_H
