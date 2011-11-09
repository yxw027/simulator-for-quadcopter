#ifndef SERIAL_PLUGIN_H
#define SERIAL_PLUGIN_H

#include <extensionsystem/iplugin.h>

#include <QtCore/QtPlugin>

namespace Serial {

namespace Internal {

class SerialPlugin : public SystemExtension::IPlugin
{
    Q_OBJECT

public:
    SerialPlugin();
    virtual ~SerialPlugin();
    
    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
};

} // namespace Internal
} // namespace Serial

#endif // SERIAL_PLUGIN_H
