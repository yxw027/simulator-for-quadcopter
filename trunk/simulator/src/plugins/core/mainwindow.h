#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace core {

class ActionManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:    
    MainWindow();
    ~MainWindow();
    
    bool init(QString *errorMessage);
    void extenstionInitialized();
    void aboutToShutdown();
    
    Core::ActionManager *actionManager() const;
    
public slots:
    void newFile();
    void exit();
    
protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *e);

private:
    QAction *mNewAction;
    QAction *mexitAction;
};

} // namespace core

#endif // MAIN_WINDOW_H