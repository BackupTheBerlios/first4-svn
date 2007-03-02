/********************************************************************************
** Form generated from reading ui file 'cmntfrm.ui'
**
** Created: Thu Mar 1 12:03:11 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CMNTFRM_H
#define UI_CMNTFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

class Ui_cmntfrm
{
public:
    QPushButton *btncancel;
    QTextEdit *txtcomments;
    QPushButton *btnok;

    void setupUi(QDialog *cmntfrm)
    {
    cmntfrm->setObjectName(QString::fromUtf8("cmntfrm"));
    cmntfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    btncancel = new QPushButton(cmntfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(10, 460, 75, 27));
    txtcomments = new QTextEdit(cmntfrm);
    txtcomments->setObjectName(QString::fromUtf8("txtcomments"));
    txtcomments->setGeometry(QRect(10, 10, 571, 441));
    btnok = new QPushButton(cmntfrm);
    btnok->setObjectName(QString::fromUtf8("btnok"));
    btnok->setGeometry(QRect(510, 460, 75, 27));

    retranslateUi(cmntfrm);

    QSize size(592, 493);
    size = size.expandedTo(cmntfrm->minimumSizeHint());
    cmntfrm->resize(size);

    QObject::connect(btnok, SIGNAL(clicked()), cmntfrm, SLOT(accept()));
    QObject::connect(btncancel, SIGNAL(clicked()), cmntfrm, SLOT(reject()));

    QMetaObject::connectSlotsByName(cmntfrm);
    } // setupUi

    void retranslateUi(QDialog *cmntfrm)
    {
    cmntfrm->setWindowTitle(QApplication::translate("cmntfrm", "Comments...", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("cmntfrm", "Cancel", 0, QApplication::UnicodeUTF8));
    btnok->setText(QApplication::translate("cmntfrm", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(cmntfrm);
    } // retranslateUi

};

namespace Ui {
    class cmntfrm: public Ui_cmntfrm {};
} // namespace Ui

#endif // UI_CMNTFRM_H
