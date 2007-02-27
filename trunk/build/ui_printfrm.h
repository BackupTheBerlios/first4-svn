/********************************************************************************
** Form generated from reading ui file 'printfrm.ui'
**
** Created: Tue Feb 27 17:21:49 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PRINTFRM_H
#define UI_PRINTFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

class Ui_printfrm
{
public:
    QPushButton *btncancel;
    QPushButton *btnok;
    QGroupBox *grpprint;
    QRadioButton *rdbtn_4;
    QRadioButton *rdbtn_2;
    QRadioButton *rdbtn_3;
    QRadioButton *rdbtn_1;

    void setupUi(QDialog *printfrm)
    {
    printfrm->setObjectName(QString::fromUtf8("printfrm"));
    printfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    btncancel = new QPushButton(printfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(10, 170, 75, 27));
    btnok = new QPushButton(printfrm);
    btnok->setObjectName(QString::fromUtf8("btnok"));
    btnok->setGeometry(QRect(250, 170, 75, 27));
    grpprint = new QGroupBox(printfrm);
    grpprint->setObjectName(QString::fromUtf8("grpprint"));
    grpprint->setGeometry(QRect(10, 10, 321, 151));
    rdbtn_4 = new QRadioButton(grpprint);
    rdbtn_4->setObjectName(QString::fromUtf8("rdbtn_4"));
    rdbtn_4->setGeometry(QRect(20, 110, 281, 23));
    rdbtn_2 = new QRadioButton(grpprint);
    rdbtn_2->setObjectName(QString::fromUtf8("rdbtn_2"));
    rdbtn_2->setGeometry(QRect(20, 50, 281, 23));
    rdbtn_3 = new QRadioButton(grpprint);
    rdbtn_3->setObjectName(QString::fromUtf8("rdbtn_3"));
    rdbtn_3->setGeometry(QRect(20, 80, 281, 23));
    rdbtn_1 = new QRadioButton(grpprint);
    rdbtn_1->setObjectName(QString::fromUtf8("rdbtn_1"));
    rdbtn_1->setGeometry(QRect(20, 20, 281, 23));

    retranslateUi(printfrm);

    QSize size(341, 203);
    size = size.expandedTo(printfrm->minimumSizeHint());
    printfrm->resize(size);

    QObject::connect(btnok, SIGNAL(clicked()), printfrm, SLOT(accept()));
    QObject::connect(btncancel, SIGNAL(clicked()), printfrm, SLOT(reject()));

    QMetaObject::connectSlotsByName(printfrm);
    } // setupUi

    void retranslateUi(QDialog *printfrm)
    {
    printfrm->setWindowTitle(QApplication::translate("printfrm", "Print...", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("printfrm", "Cancel", 0, QApplication::UnicodeUTF8));
    btnok->setText(QApplication::translate("printfrm", "OK", 0, QApplication::UnicodeUTF8));
    grpprint->setTitle(QApplication::translate("printfrm", "Print", 0, QApplication::UnicodeUTF8));
    rdbtn_4->setText(QApplication::translate("printfrm", "Print selected entries (Single)", 0, QApplication::UnicodeUTF8));
    rdbtn_2->setText(QApplication::translate("printfrm", "Print all (Single)", 0, QApplication::UnicodeUTF8));
    rdbtn_3->setText(QApplication::translate("printfrm", "Print selected entries (Table)", 0, QApplication::UnicodeUTF8));
    rdbtn_1->setText(QApplication::translate("printfrm", "Print all (Table)", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(printfrm);
    } // retranslateUi

};

namespace Ui {
    class printfrm: public Ui_printfrm {};
} // namespace Ui

#endif // UI_PRINTFRM_H
