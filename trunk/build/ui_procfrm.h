/********************************************************************************
** Form generated from reading ui file 'procfrm.ui'
**
** Created: Wed Feb 7 10:56:31 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PROCFRM_H
#define UI_PROCFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QWidget>

class Ui_Form
{
public:

    void setupUi(QWidget *Form)
    {
    Form->setObjectName(QString::fromUtf8("Form"));

    retranslateUi(Form);

    QSize size(400, 300);
    size = size.expandedTo(Form->minimumSizeHint());
    Form->resize(size);


    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

#endif // UI_PROCFRM_H
