#ifndef ACTION_CONTAINER_H
#define ACTION_CONTAINER_H

#include <QtCore/QObject>

namespace core {

class Command;

class ActionContainer : public QObject
{
    Q_OBJECT
    
public:
    ActionContainer() {}
    virtual ~ActionContainer() {}
    
    virtual int id() const = 0;
    
    virtual QMenu *menu() const = 0;
    virtual QMenuBar *menuBar() const = 0;
    
    //virtual void addAction(Command *action, const QString &);
};

} // namespace core

#endif // ACTION_CONTAINER_H