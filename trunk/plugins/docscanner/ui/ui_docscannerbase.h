/********************************************************************************
** Form generated from reading ui file 'docscannerbase.ui'
**
** Created: Sun Jun 10 21:55:35 2007
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DOCSCANNERBASE_H
#define UI_DOCSCANNERBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

class Ui_UiDocScannerBase
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBoxCustomer;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *labelCustomer;
    QComboBox *cbxCustomer;
    QPushButton *btnNewCustomer;
    QGridLayout *gridLayout2;
    QLabel *labelDescription;
    QSpacerItem *spacerItem;
    QTextBrowser *textBrowserPreview;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *btnScan;
    QPushButton *btnAbort;

    void setupUi(QWidget *UiDocScannerBase)
    {
    UiDocScannerBase->setObjectName(QString::fromUtf8("UiDocScannerBase"));
    gridLayout = new QGridLayout(UiDocScannerBase);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    groupBoxCustomer = new QGroupBox(UiDocScannerBase);
    groupBoxCustomer->setObjectName(QString::fromUtf8("groupBoxCustomer"));
    gridLayout1 = new QGridLayout(groupBoxCustomer);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(9);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    labelCustomer = new QLabel(groupBoxCustomer);
    labelCustomer->setObjectName(QString::fromUtf8("labelCustomer"));
    labelCustomer->setMinimumSize(QSize(110, 0));
    labelCustomer->setMaximumSize(QSize(110, 16777215));

    hboxLayout->addWidget(labelCustomer);

    cbxCustomer = new QComboBox(groupBoxCustomer);
    cbxCustomer->setObjectName(QString::fromUtf8("cbxCustomer"));

    hboxLayout->addWidget(cbxCustomer);

    btnNewCustomer = new QPushButton(groupBoxCustomer);
    btnNewCustomer->setObjectName(QString::fromUtf8("btnNewCustomer"));
    btnNewCustomer->setMinimumSize(QSize(22, 22));
    btnNewCustomer->setMaximumSize(QSize(22, 22));

    hboxLayout->addWidget(btnNewCustomer);


    gridLayout1->addLayout(hboxLayout, 0, 0, 1, 1);

    gridLayout2 = new QGridLayout();
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(0);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    labelDescription = new QLabel(groupBoxCustomer);
    labelDescription->setObjectName(QString::fromUtf8("labelDescription"));
    labelDescription->setMinimumSize(QSize(110, 0));
    labelDescription->setMaximumSize(QSize(110, 16777215));

    gridLayout2->addWidget(labelDescription, 0, 0, 1, 1);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout2->addItem(spacerItem, 1, 0, 1, 1);

    textBrowserPreview = new QTextBrowser(groupBoxCustomer);
    textBrowserPreview->setObjectName(QString::fromUtf8("textBrowserPreview"));
    textBrowserPreview->setOpenExternalLinks(true);

    gridLayout2->addWidget(textBrowserPreview, 0, 1, 2, 1);


    gridLayout1->addLayout(gridLayout2, 1, 0, 1, 1);


    gridLayout->addWidget(groupBoxCustomer, 0, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);

    btnScan = new QPushButton(UiDocScannerBase);
    btnScan->setObjectName(QString::fromUtf8("btnScan"));

    hboxLayout1->addWidget(btnScan);

    btnAbort = new QPushButton(UiDocScannerBase);
    btnAbort->setObjectName(QString::fromUtf8("btnAbort"));

    hboxLayout1->addWidget(btnAbort);


    gridLayout->addLayout(hboxLayout1, 1, 0, 1, 1);

    labelCustomer->setBuddy(cbxCustomer);
    labelDescription->setBuddy(textBrowserPreview);
    QWidget::setTabOrder(cbxCustomer, textBrowserPreview);
    QWidget::setTabOrder(textBrowserPreview, btnScan);
    QWidget::setTabOrder(btnScan, btnAbort);

    retranslateUi(UiDocScannerBase);

    QSize size(663, 489);
    size = size.expandedTo(UiDocScannerBase->minimumSizeHint());
    UiDocScannerBase->resize(size);

    QObject::connect(btnAbort, SIGNAL(clicked()), UiDocScannerBase, SLOT(close()));

    QMetaObject::connectSlotsByName(UiDocScannerBase);
    } // setupUi

    void retranslateUi(QWidget *UiDocScannerBase)
    {
    UiDocScannerBase->setWindowTitle(QApplication::translate("UiDocScannerBase", "Scan documents", 0, QApplication::UnicodeUTF8));
    groupBoxCustomer->setTitle(QApplication::translate("UiDocScannerBase", "Documents", 0, QApplication::UnicodeUTF8));
    labelCustomer->setText(QApplication::translate("UiDocScannerBase", "Customer:", 0, QApplication::UnicodeUTF8));
    btnNewCustomer->setText(QApplication::translate("UiDocScannerBase", "...", 0, QApplication::UnicodeUTF8));
    labelDescription->setText(QApplication::translate("UiDocScannerBase", "Preview:", 0, QApplication::UnicodeUTF8));
    btnScan->setText(QApplication::translate("UiDocScannerBase", "&Scan", 0, QApplication::UnicodeUTF8));
    btnAbort->setText(QApplication::translate("UiDocScannerBase", "&Abort", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(UiDocScannerBase);
    } // retranslateUi

};

namespace Ui {
    class UiDocScannerBase: public Ui_UiDocScannerBase {};
} // namespace Ui

#endif // UI_DOCSCANNERBASE_H
