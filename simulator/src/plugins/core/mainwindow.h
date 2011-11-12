#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

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
class CORE_EXPORT MainWindow : public EventFilteringMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();
    
    bool init(QString *errorMessage);
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

    QAction *mNewAction;
    QAction *mexitAction;
};

} // namespace Internal
} // namespace Core

#endif // MAINWINDOW_H
