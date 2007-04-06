/********************************************************************************
** Form generated from reading ui file 'invnewfrm.ui'
**
** Created: Thu Apr 5 22:13:13 2007
**      by: Qt User Interface Compiler version 4.3.0beta
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INVNEWFRM_H
#define UI_INVNEWFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

class Ui_invnewfrm
{
public:
    QPushButton *btncreate;
    QPushButton *btncancel;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *txtcomments;
    QComboBox *cmbinv;

    void setupUi(QDialog *invnewfrm)
    {
    if (invnewfrm->objectName().isEmpty())
        invnewfrm->setObjectName(QString::fromUtf8("invnewfrm"));
    QSize size(441, 253);
    size = size.expandedTo(invnewfrm->minimumSizeHint());
    invnewfrm->resize(size);
    invnewfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/kfm.png")));
    btncreate = new QPushButton(invnewfrm);
    btncreate->setObjectName(QString::fromUtf8("btncreate"));
    btncreate->setGeometry(QRect(360, 220, 75, 27));
    btncancel = new QPushButton(invnewfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(10, 220, 75, 27));
    label = new QLabel(invnewfrm);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 10, 141, 17));
    label_2 = new QLabel(invnewfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 50, 141, 17));
    txtcomments = new QTextEdit(invnewfrm);
    txtcomments->setObjectName(QString::fromUtf8("txtcomments"));
    txtcomments->setGeometry(QRect(160, 50, 271, 161));
    cmbinv = new QComboBox(invnewfrm);
    cmbinv->setObjectName(QString::fromUtf8("cmbinv"));
    cmbinv->setGeometry(QRect(160, 10, 271, 22));

    retranslateUi(invnewfrm);
    QObject::connect(btncreate, SIGNAL(clicked()), invnewfrm, SLOT(accept()));
    QObject::connect(btncancel, SIGNAL(clicked()), invnewfrm, SLOT(reject()));

    QMetaObject::connectSlotsByName(invnewfrm);
    } // setupUi

    void retranslateUi(QDialog *invnewfrm)
    {
    invnewfrm->setWindowTitle(QApplication::translate("invnewfrm", "New inventory from...", 0, QApplication::UnicodeUTF8));
    btncreate->setText(QApplication::translate("invnewfrm", "OK", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("invnewfrm", "Cancel", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("invnewfrm", "Inventory from:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("invnewfrm", "Comments:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(invnewfrm);
    } // retranslateUi

};

namespace Ui {
    class invnewfrm: public Ui_invnewfrm {};
} // namespace Ui

#endif // UI_INVNEWFRM_H
