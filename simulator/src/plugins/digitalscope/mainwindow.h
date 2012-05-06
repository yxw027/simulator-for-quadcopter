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
    void about();

private:
    void createMenu();
    void createActions();

    QWidget *centralWidget;

    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction *m_exitAction;

    QAction *m_aboutAction;
    QAction *m_aboutQtAction;
    Plot *plot;
};

#endif // MAINWINDOW_H
