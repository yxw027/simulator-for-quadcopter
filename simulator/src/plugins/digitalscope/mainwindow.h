#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
class QStatusBar;
class GLWidget;
class Plot;
class QwtPlotPicker;
class QwtPlotPanner;
class QwtPlotZoomer;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void newFile();
    void exit();

    void pickerMoved(const QPoint &);

    void about();
//    void enableZoomMode(bool);
    void zoomIn();
    void zoomOut();
protected:
    // virtual void changeEvent(QEvent *e);
    // virtual void closeEvent(QCloseEvent *event);
    // virtual void contextMenuEvent(QContextMenuEvent *event);
private:
    void createMenu();
    void createToolBar();

    QWidget *centralWidget;

    QMenu *fileMenu;
    QMenu *helpMenu;
    
    QAction *m_newAction;
    QAction *m_exitAction;


    QAction *m_aboutAction;
    QAction *m_aboutQtAction;


    GLWidget *glWidget;
    Plot *plot;
    QwtPlotPicker *m_picker;
    QwtPlotPanner *m_panner;
    QwtPlotZoomer *m_zoomer;
};

#endif // MAINWINDOW_H
