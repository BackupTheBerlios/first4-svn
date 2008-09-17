/********************************************************************************
** Form generated from reading ui file 'cashpoint.ui'
**
** Created: Tue 16. Sep 15:14:11 2008
**      by: Qt User Interface Compiler version 4.3.4
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CASHPOINT_H
#define UI_CASHPOINT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QWidget>

class Ui_cashpoint_main
{
public:

    void setupUi(QWidget *cashpoint_main)
    {
    if (cashpoint_main->objectName().isEmpty())
        cashpoint_main->setObjectName(QString::fromUtf8("cashpoint_main"));
    cashpoint_main->resize(400, 300);
    cashpoint_main->setWindowIcon(QIcon(QString::fromUtf8(":/kcalc.png")));

    retranslateUi(cashpoint_main);

    QMetaObject::connectSlotsByName(cashpoint_main);
    } // setupUi

    void retranslateUi(QWidget *cashpoint_main)
    {
    cashpoint_main->setWindowTitle(QApplication::translate("cashpoint_main", "first4 - Cashpoint", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(cashpoint_main);
    } // retranslateUi

};

namespace Ui {
    class cashpoint_main: public Ui_cashpoint_main {};
} // namespace Ui

#endif // UI_CASHPOINT_H
