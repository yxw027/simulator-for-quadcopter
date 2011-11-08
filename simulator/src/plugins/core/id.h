#ifndef CORE_ID_H
#define CORE_ID_H

#include "core_global.h"

#include <QtCore/QMetaType>
#include <QtCore/QString>

namespace core {

class CORE_EXPORT Id
{
public:
    Id() {}
    Id(const char *name) : mName(name) {}
    Id(const QByteArray &name) : mName(name) {}
    
    QByteArray name() const { return mName; }
    QString toString() const { return QString::fromLatin1(mName); }
    bool isValid() const { return !mName.isEmpty(); }
    bool operator==(const Id &id) const { return mName == id.mName; }
    bool operator!=(const Id &id) const { return mName != id.mName; }
    
private:
    QByteArray mName;
};

} // namespace core

#endif // CORE_ID_H