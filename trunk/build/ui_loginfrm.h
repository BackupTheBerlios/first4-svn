/********************************************************************************
** Form generated from reading ui file 'loginfrm.ui'
**
** Created: Tue Feb 27 17:21:49 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOGINFRM_H
#define UI_LOGINFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_loginfrm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *boxuser;
    QLineEdit *boxpwd;
    QComboBox *cmbdb;
    QPushButton *btnok;
    QPushButton *btncancel;

    void setupUi(QDialog *loginfrm)
    {
    loginfrm->setObjectName(QString::fromUtf8("loginfrm"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(loginfrm->sizePolicy().hasHeightForWidth());
    loginfrm->setSizePolicy(sizePolicy);
    loginfrm->setMinimumSize(QSize(352, 180));
    loginfrm->setMaximumSize(QSize(352, 176));
    loginfrm->setBaseSize(QSize(0, 0));
    loginfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    label = new QLabel(loginfrm);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 20, 101, 20));
    label_2 = new QLabel(loginfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 60, 101, 20));
    label_3 = new QLabel(loginfrm);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(10, 100, 101, 20));
    boxuser = new QLineEdit(loginfrm);
    boxuser->setObjectName(QString::fromUtf8("boxuser"));
    boxuser->setGeometry(QRect(120, 20, 221, 25));
    boxpwd = new QLineEdit(loginfrm);
    boxpwd->setObjectName(QString::fromUtf8("boxpwd"));
    boxpwd->setGeometry(QRect(120, 60, 221, 25));
    boxpwd->setEchoMode(QLineEdit::Password);
    cmbdb = new QComboBox(loginfrm);
    cmbdb->setObjectName(QString::fromUtf8("cmbdb"));
    cmbdb->setGeometry(QRect(120, 100, 221, 22));
    btnok = new QPushButton(loginfrm);
    btnok->setObjectName(QString::fromUtf8("btnok"));
    btnok->setGeometry(QRect(10, 140, 75, 30));
    btnok->setDefault(true);
    btncancel = new QPushButton(loginfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(270, 140, 75, 30));
    QWidget::setTabOrder(boxuser, boxpwd);
    QWidget::setTabOrder(boxpwd, cmbdb);
    QWidget::setTabOrder(cmbdb, btnok);
    QWidget::setTabOrder(btnok, btncancel);

    retranslateUi(loginfrm);

    QSize size(352, 180);
    size = size.expandedTo(loginfrm->minimumSizeHint());
    loginfrm->resize(size);

    QObject::connect(btncancel, SIGNAL(clicked()), loginfrm, SLOT(reject()));

    QMetaObject::connectSlotsByName(loginfrm);
    } // setupUi

    void retranslateUi(QDialog *loginfrm)
    {
    loginfrm->setWindowTitle(QApplication::translate("loginfrm", "Login...", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("loginfrm", "Username:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("loginfrm", "Password:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("loginfrm", "Database:", 0, QApplication::UnicodeUTF8));
    btnok->setText(QApplication::translate("loginfrm", "OK", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("loginfrm", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(loginfrm);
    } // retranslateUi

};

namespace Ui {
    class loginfrm: public Ui_loginfrm {};
} // namespace Ui

#endif // UI_LOGINFRM_H
