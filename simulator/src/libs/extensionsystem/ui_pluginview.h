/********************************************************************************
** Form generated from reading UI file 'pluginview.ui'
**
** Created: Sat Nov 5 17:24:13 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINVIEW_H
#define UI_PLUGINVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

namespace ExtensionSystem {
namespace Internal {

class Ui_PluginView
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *categoryWidget;

    void setupUi(QWidget *ExtensionSystem__Internal__PluginView)
    {
        if (ExtensionSystem__Internal__PluginView->objectName().isEmpty())
            ExtensionSystem__Internal__PluginView->setObjectName(QString::fromUtf8("ExtensionSystem__Internal__PluginView"));
        ExtensionSystem__Internal__PluginView->resize(773, 304);
        gridLayout = new QGridLayout(ExtensionSystem__Internal__PluginView);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        categoryWidget = new QTreeWidget(ExtensionSystem__Internal__PluginView);
        categoryWidget->setObjectName(QString::fromUtf8("categoryWidget"));
        categoryWidget->setAlternatingRowColors(true);
        categoryWidget->setIndentation(20);
        categoryWidget->setRootIsDecorated(true);
        categoryWidget->setUniformRowHeights(false);
        categoryWidget->setItemsExpandable(true);
        categoryWidget->setSortingEnabled(true);
        categoryWidget->setColumnCount(4);
        categoryWidget->header()->setDefaultSectionSize(120);
        categoryWidget->header()->setHighlightSections(false);
        categoryWidget->header()->setMinimumSectionSize(35);

        gridLayout->addWidget(categoryWidget, 1, 0, 1, 1);


        retranslateUi(ExtensionSystem__Internal__PluginView);

        QMetaObject::connectSlotsByName(ExtensionSystem__Internal__PluginView);
    } // setupUi

    void retranslateUi(QWidget *ExtensionSystem__Internal__PluginView)
    {
        QTreeWidgetItem *___qtreewidgetitem = categoryWidget->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("ExtensionSystem::Internal::PluginView", "Vendor", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(2, QApplication::translate("ExtensionSystem::Internal::PluginView", "Version", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("ExtensionSystem::Internal::PluginView", "Load", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("ExtensionSystem::Internal::PluginView", "Name", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ExtensionSystem__Internal__PluginView);
    } // retranslateUi

};

} // namespace Internal
} // namespace ExtensionSystem

namespace ExtensionSystem {
namespace Internal {
namespace Ui {
    class PluginView: public Ui_PluginView {};
} // namespace Ui
} // namespace Internal
} // namespace ExtensionSystem

#endif // UI_PLUGINVIEW_H
