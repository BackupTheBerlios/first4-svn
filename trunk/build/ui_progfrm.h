/********************************************************************************
** Form generated from reading ui file 'progfrm.ui'
**
** Created: Tue Feb 27 17:21:49 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PROGFRM_H
#define UI_PROGFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QProgressBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

class Ui_progfrm
{
public:
    QProgressBar *progbar;
    QTextEdit *txtcomments;

    void setupUi(QWidget *progfrm)
    {
    progfrm->setObjectName(QString::fromUtf8("progfrm"));
    progfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    progbar = new QProgressBar(progfrm);
    progbar->setObjectName(QString::fromUtf8("progbar"));
    progbar->setGeometry(QRect(10, 10, 381, 23));
    progbar->setValue(24);
    progbar->setOrientation(Qt::Horizontal);
    txtcomments = new QTextEdit(progfrm);
    txtcomments->setObjectName(QString::fromUtf8("txtcomments"));
    txtcomments->setGeometry(QRect(10, 40, 381, 111));

    retranslateUi(progfrm);

    QSize size(401, 159);
    size = size.expandedTo(progfrm->minimumSizeHint());
    progfrm->resize(size);


    QMetaObject::connectSlotsByName(progfrm);
    } // setupUi

    void retranslateUi(QWidget *progfrm)
    {
    progfrm->setWindowTitle(QApplication::translate("progfrm", "Progress...", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(progfrm);
    } // retranslateUi

};

namespace Ui {
    class progfrm: public Ui_progfrm {};
} // namespace Ui

#endif // UI_PROGFRM_H
