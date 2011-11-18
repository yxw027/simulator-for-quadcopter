#ifndef IPLUGINCONTEXT_H
#define IPLUGINCONTEXT_H

namespace ExtensionSystem {

class EXTENSIONSYSTEM_EXPORT IPluginContext
{
public:
    IPluginContext() {}
    virtual ~IPluginContext() {}
    
    virtual QString pluginContextString() const = 0;
};

} // namespace ExtensionSystem

#endif // IPLUGINCONTEXT_H