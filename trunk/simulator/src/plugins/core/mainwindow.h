#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core_global.h"

#include "eventfilteringmainwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMenu;
class QShortcut;
class QToolButton;
class MyTabWidget;
QT_END_NAMESPACE

namespace Core {

class ActionManager;


namespace Internal {

class CoreImpl;
class CORE_EXPORT MainWindow : public EventFilteringMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();
    
    bool initialize(QString *errorMessage);
    void extensionsInitialized();
    void aboutToShutdown();
    
    Core::ActionManager *actionManager() const;
    
public slots:
    // void newFile();
    // void exit();
    
protected:
    // virtual void changeEvent(QEvent *e);
    // virtual void closeEvent(QCloseEvent *event);

private slots:
private:
    QWidget *centralWidget;
    QMenu *fileMenu;

    CoreImpl *m_coreImpl;
    ActionManagerPrivate *m_actionManager;
    QAction *mNewAction;
    QAction *mexitAction;
};

} // namespace Internal
} // namespace Core

#endif // MAINWINDOW_H
