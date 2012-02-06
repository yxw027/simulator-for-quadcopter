#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
class QStatusBar;
class QPushButton;
class QComboBox;
class GLWidget;
class Plot;
class QwtPlotPicker;
class QwtPlotPanner;
class QwtPlotZoomer;
class QextSerialPort;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

signals:
    void running(bool);

public slots:
    void newFile();
    void exit();

    void pickerMoved(const QPoint &);

    void about();
//    void enableZoomMode(bool);
    void zoomIn();
    void zoomOut();

    void serialConnection();
    void onReadyRead();
protected:
    // virtual void changeEvent(QEvent *e);
    // virtual void closeEvent(QCloseEvent *event);
    // virtual void contextMenuEvent(QContextMenuEvent *event);
private:
    void createActions();
    void createMenu();
    void createToolBar();

    QStringList getPorts();
    void openSerialPort(const QString& name);
    void closeSerialPort(const QString& name);

    QWidget *centralWidget;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;

    QAction *m_newAction;
    QAction *m_exitAction;

    QAction *m_zoomInAction;
    QAction *m_zoomOutAction;
    QAction *m_aboutAction;
    QAction *m_aboutQtAction;

    QToolBar *m_fileToolBar;
    QToolBar *m_viewToolBar;
    QPushButton *m_serialConnection;
    QComboBox *m_combobox;

    GLWidget *glWidget;
    Plot *plot;
    QwtPlotPicker *m_picker;
    QwtPlotPanner *m_panner;
    QwtPlotZoomer *m_zoomer;

    QextSerialPort *port;
    bool m_connected;
};

#endif // MAINWINDOW_H
