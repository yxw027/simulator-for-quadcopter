#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    SerialDialog(QWidget *parent = 0);
    ~SerialDialog();

signals:
    void serialConfigChanged();

private:
    QLabel *nameLabel;
    QLabel *mLabel;
    QLabel *mLabel;
    QLabel *mLabel;
    QLabel *mLabel;
    QLabel *mLabel;

    QCombox nameCombox;
    QPushButton *okButton;
    QPushButton *cancelButton;    
};

#endif // SERIALDIALOG_H