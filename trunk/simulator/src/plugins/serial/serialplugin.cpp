#include "serial.h"

SerialPlugin::SerialPlugin()
{
}

SerialPlugin::~SerialPlugin()
{
}

bool SerialPlugin::initialize(const QString &args, QString *errMsg)
{
    Q_UNUSED(args);
    Q_UNUSED(errMsg);
    
    return true;
}

void SerialPlugin::extensionInitialized()
{
}

void SerialPlugin::shutdown()
{
}

Q_EXPROT_PLUGIN(SerialPlugin)