#include "serial.h"

namespace Serial {
namespace Internal {

SerialPlugin::SerialPlugin()
{
}

SerialPlugin::~SerialPlugin()
{
}

bool SerialPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage);
    
    return true;
}

void SerialPlugin::extensionsInitialized()
{
}

} // namespace Internal
} // namespace Serial

Q_EXPORT_PLUGIN(Serial::Internal::SerialPlugin)