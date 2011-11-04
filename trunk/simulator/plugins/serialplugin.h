#ifndef SERIAL_PLUGIN_H
#define SERIAL_PLUGIN_H

#include <QString>

class SerialPlugin {
public:
    virtual ~SerialPlugin() {}
    virtual QString deviceName() = 0;
};

Q_DECLARE_INTERFACE(SeriaPlugin, "com.OpenRL.Plugin.SeriaPlugin/0.1");

#endif // SERIAL_PLUGIN_H
