#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>

class QLabel;
class QComboBox;
class QPushButton;

class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    SerialDialog(QWidget *parent = 0);
    ~SerialDialog();

    QSize sizeHint() const;

signals:
    void serialConfigChanged();
private slots:
    void serialPortChanged(QString string);

public slots:
    void serialConnect();

private:
    QLabel *mLabelPort;
    QLabel *mLabelBaudRate;
    QLabel *mLabelDataBits;
    QLabel *mLabelStopBits;
    QLabel *mLabelParity;
    QLabel *mLabelFlowControl;

    QComboBox *mComboxPort;
    QComboBox *mComboxBaudRate;
    QComboBox *mComboxDataBits;
    QComboBox *mComboxStopBit;
    QComboBox *mComboxParity;
    QComboBox *mComboxFlowControl;

    QPushButton *mPushButtonOK;
    QPushButton *mPushButtonCancel;
};

#endif // SERIALDIALOG_H
