#ifndef PLUGINSPEC_H
#define PLUGINSPEC_H

#include "extensionsystem_global.h"

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QHash>

QT_BEGIN_NAMESPACE
class QStringList;
QT_END_NAMESPACE

namespace ExtensionSystem {

struct EXTENSIONSYSTEM_EXPORT PluginDependency
{
    enum Type {
        Required,
        Optional
    };

    PluginDependency() : type(Required) {}

    QString name;
    QString version;
    Type type;
    bool operator==(const PluginDependency &other) const;
};

uint qHash(const ExtensionSystem::PluginDependency &value);

struct EXTENSIONSYSTEM_EXPORT PluginArgumentDescription
{
    QString name;
    QString parameter;
    QString description;
};

class EXTENSIONSYSTEM_EXPORT PluginSpec
{
public:
    enum State { Invalid, Read, Resolved, Loaded, Initialized, Running, Stopped, Deleted };

    PluginSpec(const QString &fileName);
    ~PluginSpec();

    // information from the xml file, valid after 'Read' state is reached
    QString name() const;
    QString version() const;
    QString compatVersion() const;
    QString vendor() const;
    QString copyright() const;
    QString license() const;
    QString description() const;
    QString url() const;
    QString category() const;
    bool isExperimental() const;
    bool isDisabledByDefault() const;
    bool isEnabled() const;
    bool isDisabledIndirectly() const;
    QList<PluginDependency> dependencies() const;

    typedef QList<PluginArgumentDescription> PluginArgumentDescriptions;
    PluginArgumentDescriptions argumentDescriptions() const;

    // other information, valid after 'Read' state is reached
    QString location() const;
    QString filePath() const;

    void setEnabled(bool value);
    void setDisabledByDefault(bool value);
    void setDisabledIndirectly(bool value);

    QStringList arguments() const;
    void setArguments(const QStringList &arguments);
    void addArgument(const QString &argument);

    bool provides(const QString &pluginName, const QString &version) const;

    // dependency specs, valid after 'Resolved' state is reached
    QHash<PluginDependency, PluginSpec *> dependencySpecs() const;

    // state
    State state() const;
    bool hasError() const;
    QString errorString() const;

private:
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

//    QString location;
//    QString errorString;

//    bool enabled;
//    bool hasError;

    PluginSpec::State state;
    
    bool read(const QString &fileName);
    void readPluginSpec(QXmlStreamReader &reader);    
    void readPluginSpec(QXmlStreamReader &reader);
    void readDependencies(QXmlStreamReader &reader);
    void readArgumentDescriptions(QXmlStreamReader &reader);
    void readArgumentDescription(QXmlStreamReader &reader);    
};

} // namespace ExtensionSystem

#endif // PLUGINSPEC_H
