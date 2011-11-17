#include "iplugin.h"

#include <QDebug>

using namespace ExtensionSystem;

IPlugin::IPlugin() : QObject(0)
{
}

IPlugin::~IPlugin()
{
    for (QList<QObject* >::iterator it = this->m_objList.begin();
            it != this->m_objList.end();++it) {
        delete *it;
        *it = 0;
    }
}

IPlugin::ShutdownFlag IPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

PluginSpec *IPlugin::pluginSpec() const
{
    return this->m_spec;
}

void addObject(QObject *obj)
{
}

void IPlugin::addAutoReleasedObject(QObject *obj)
{
    if (obj == NULL) {
        qWarning() << tr("%1:%2 Try Insert Null Object").arg(__FILE__).arg(__LINE__);
        return;
    }

    if (this->m_objList.contains(obj)) {
        qWarning() << tr("%1:%2 Insert Object Already Added").arg(__FILE__).arg(__LINE__);
        return;
    }

    this->m_objList.append(obj);
}

void IPlugin::removeObject(QObject *obj)
{
}
