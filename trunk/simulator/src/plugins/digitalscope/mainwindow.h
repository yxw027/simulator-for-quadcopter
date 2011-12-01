#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
class Plot;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    // void newFile();
    void exit();

protected:
    // virtual void changeEvent(QEvent *e);
    // virtual void closeEvent(QCloseEvent *event);

private:
    createMenu();
    createToolBar();

    QWidget *centralWidget;

    QMenu *fileMenu;
    QAction *m_newAction;
    QAction *m_exitAction;

    QMenu *helpMenu;
    QAction *m_aboutAction;

    Plot *plot;
};

#endif // MAINWINDOW_H
