#ifndef PLUGINSPEC_P_H
#define PLUGINSPEC_P_H

#include "pluginspec.h"

#include <QtCore/QObject>

namespace ExtensionSystem {

namespace Internal {

class EXTENSIONSYSTEM_EXPORT PluginSpecPrivate : public QObject
{
    Q_OBJECT

public:
    PluginSpecPrivate(PluginSpec *spec);

    bool read(const QString &fileName);
    QString name;
    QString version;
    QString compatVersion;
    QString vendor;
    QString copyright;
    QString license;
    QString description;
    QString url;
    QString category;
    QList<PluginDependency> dependencies;
    PluginSpec::State state;

private:
    PluginSpec *q;
};

} // namespace Internal
} // namespace ExtensionSystem

#endif // PLUGINSPEC_P_H
