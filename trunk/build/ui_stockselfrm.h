/********************************************************************************
** Form generated from reading ui file 'stockselfrm.ui'
**
** Created: Thu Apr 5 22:13:13 2007
**      by: Qt User Interface Compiler version 4.3.0beta
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STOCKSELFRM_H
#define UI_STOCKSELFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>

class Ui_stockselfrm
{
public:
    QPushButton *btncancel;
    QPushButton *btnaccept;
    QTreeWidget *treemain;

    void setupUi(QDialog *stockselfrm)
    {
    if (stockselfrm->objectName().isEmpty())
        stockselfrm->setObjectName(QString::fromUtf8("stockselfrm"));
    QSize size(642, 393);
    size = size.expandedTo(stockselfrm->minimumSizeHint());
    stockselfrm->resize(size);
    stockselfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    btncancel = new QPushButton(stockselfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(10, 360, 75, 27));
    btnaccept = new QPushButton(stockselfrm);
    btnaccept->setObjectName(QString::fromUtf8("btnaccept"));
    btnaccept->setGeometry(QRect(560, 360, 75, 27));
    treemain = new QTreeWidget(stockselfrm);
    treemain->setObjectName(QString::fromUtf8("treemain"));
    treemain->setGeometry(QRect(10, 10, 621, 341));

    retranslateUi(stockselfrm);
    QObject::connect(btnaccept, SIGNAL(clicked()), stockselfrm, SLOT(accept()));
    QObject::connect(btncancel, SIGNAL(clicked()), stockselfrm, SLOT(reject()));
    QObject::connect(treemain, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), stockselfrm, SLOT(accept()));

    QMetaObject::connectSlotsByName(stockselfrm);
    } // setupUi

    void retranslateUi(QDialog *stockselfrm)
    {
    stockselfrm->setWindowTitle(QApplication::translate("stockselfrm", "Select stock item...", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("stockselfrm", "Cancel", 0, QApplication::UnicodeUTF8));
    btnaccept->setText(QApplication::translate("stockselfrm", "&Accept", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(0, QApplication::translate("stockselfrm", "ID", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(1, QApplication::translate("stockselfrm", "Label", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(2, QApplication::translate("stockselfrm", "Description", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(3, QApplication::translate("stockselfrm", "Stock", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(4, QApplication::translate("stockselfrm", "Unit", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(5, QApplication::translate("stockselfrm", "Price", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(6, QApplication::translate("stockselfrm", "VAT", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(7, QApplication::translate("stockselfrm", "Min. Stock", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(8, QApplication::translate("stockselfrm", "tab_id", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(stockselfrm);
    } // retranslateUi

};

namespace Ui {
    class stockselfrm: public Ui_stockselfrm {};
} // namespace Ui

#endif // UI_STOCKSELFRM_H
