/********************************************************************************
** Form generated from reading UI file 'pluginerroroverview.ui'
**
** Created: Fri Nov 11 23:00:55 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINERROROVERVIEW_H
#define UI_PLUGINERROROVERVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

namespace ExtensionSystem {
namespace Internal {

class Ui_PluginErrorOverview
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *pluginList;
    QLabel *label_2;
    QTextEdit *pluginError;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExtensionSystem__Internal__PluginErrorOverview)
    {
        if (ExtensionSystem__Internal__PluginErrorOverview->objectName().isEmpty())
            ExtensionSystem__Internal__PluginErrorOverview->setObjectName(QString::fromUtf8("ExtensionSystem__Internal__PluginErrorOverview"));
        ExtensionSystem__Internal__PluginErrorOverview->resize(434, 361);
        verticalLayout = new QVBoxLayout(ExtensionSystem__Internal__PluginErrorOverview);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ExtensionSystem__Internal__PluginErrorOverview);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        pluginList = new QListWidget(ExtensionSystem__Internal__PluginErrorOverview);
        pluginList->setObjectName(QString::fromUtf8("pluginList"));

        verticalLayout->addWidget(pluginList);

        label_2 = new QLabel(ExtensionSystem__Internal__PluginErrorOverview);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        pluginError = new QTextEdit(ExtensionSystem__Internal__PluginErrorOverview);
        pluginError->setObjectName(QString::fromUtf8("pluginError"));
        pluginError->setReadOnly(true);

        verticalLayout->addWidget(pluginError);

        buttonBox = new QDialogButtonBox(ExtensionSystem__Internal__PluginErrorOverview);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::NoButton);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ExtensionSystem__Internal__PluginErrorOverview);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExtensionSystem__Internal__PluginErrorOverview, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExtensionSystem__Internal__PluginErrorOverview, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExtensionSystem__Internal__PluginErrorOverview);
    } // setupUi

    void retranslateUi(QDialog *ExtensionSystem__Internal__PluginErrorOverview)
    {
        ExtensionSystem__Internal__PluginErrorOverview->setWindowTitle(QApplication::translate("ExtensionSystem::Internal::PluginErrorOverview", "Qt Creator - Plugin loader messages", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ExtensionSystem::Internal::PluginErrorOverview", "The following plugins have errors and cannot be loaded:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ExtensionSystem::Internal::PluginErrorOverview", "Details:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

} // namespace Internal
} // namespace ExtensionSystem

namespace ExtensionSystem {
namespace Internal {
namespace Ui {
    class PluginErrorOverview: public Ui_PluginErrorOverview {};
} // namespace Ui
} // namespace Internal
} // namespace ExtensionSystem

#endif // UI_PLUGINERROROVERVIEW_H
