#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();
    
public slots:
    // void newFile();
    // void exit();
    
protected:
    // virtual void changeEvent(QEvent *e);
    // virtual void closeEvent(QCloseEvent *event);

private:
    QWidget *centralWidget;
    QMenu *fileMenu;
/*
    CoreImpl *m_coreImpl;
    ActionManagerPrivate *m_actionManager;
    QAction *mNewAction;
    QAction *mexitAction;*/
};

#endif // MAINWINDOW_H
