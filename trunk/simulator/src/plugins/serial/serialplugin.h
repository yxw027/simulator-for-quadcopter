#ifndef SERIAL_PLUGIN_H
#define SERIAL_PLUGIN_H

#include <extensionsystem/iplugin.h>

class SerialPlugin : public SystemExtension::IPlugin
{
public:
    SerialPlugin();
    virtual ~SerialPlugin();
    
    void extensionInitialized();
    bool initialize(const QString &arguments, QString *errorString);
    void shutdown();
};

#endif // SERIAL_PLUGIN_H
