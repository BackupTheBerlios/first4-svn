/********************************************************************************
** Form generated from reading ui file 'newdbfrm.ui'
**
** Created: Tue Feb 27 17:21:49 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NEWDBFRM_H
#define UI_NEWDBFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

class Ui_newdbfrm
{
public:
    QStackedWidget *mainwidget;
    QWidget *page;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QPushButton *btncancel;
    QLineEdit *txthost;
    QLineEdit *txtuser;
    QLineEdit *txtpwd;
    QPushButton *btnnext;
    QLineEdit *txtport;
    QLabel *label_6;
    QWidget *page_2;
    QLabel *label_5;
    QPushButton *btnfinish;
    QPushButton *btncancel_2;
    QComboBox *cmbdb;

    void setupUi(QDialog *newdbfrm)
    {
    newdbfrm->setObjectName(QString::fromUtf8("newdbfrm"));
    newdbfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    mainwidget = new QStackedWidget(newdbfrm);
    mainwidget->setObjectName(QString::fromUtf8("mainwidget"));
    mainwidget->setGeometry(QRect(0, 0, 431, 241));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    label_4 = new QLabel(page);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(20, 140, 91, 20));
    label_3 = new QLabel(page);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(20, 100, 91, 20));
    label_2 = new QLabel(page);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(20, 60, 91, 20));
    label = new QLabel(page);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(20, 20, 221, 20));
    btncancel = new QPushButton(page);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(20, 190, 82, 30));
    txthost = new QLineEdit(page);
    txthost->setObjectName(QString::fromUtf8("txthost"));
    txthost->setGeometry(QRect(120, 60, 171, 28));
    txtuser = new QLineEdit(page);
    txtuser->setObjectName(QString::fromUtf8("txtuser"));
    txtuser->setGeometry(QRect(120, 100, 291, 28));
    txtpwd = new QLineEdit(page);
    txtpwd->setObjectName(QString::fromUtf8("txtpwd"));
    txtpwd->setGeometry(QRect(120, 140, 291, 28));
    txtpwd->setEchoMode(QLineEdit::Password);
    btnnext = new QPushButton(page);
    btnnext->setObjectName(QString::fromUtf8("btnnext"));
    btnnext->setGeometry(QRect(330, 190, 82, 30));
    txtport = new QLineEdit(page);
    txtport->setObjectName(QString::fromUtf8("txtport"));
    txtport->setGeometry(QRect(352, 60, 61, 28));
    label_6 = new QLabel(page);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(310, 60, 41, 20));
    mainwidget->addWidget(page);
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    label_5 = new QLabel(page_2);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(20, 30, 101, 20));
    btnfinish = new QPushButton(page_2);
    btnfinish->setObjectName(QString::fromUtf8("btnfinish"));
    btnfinish->setGeometry(QRect(300, 190, 82, 30));
    btncancel_2 = new QPushButton(page_2);
    btncancel_2->setObjectName(QString::fromUtf8("btncancel_2"));
    btncancel_2->setGeometry(QRect(20, 190, 82, 30));
    cmbdb = new QComboBox(page_2);
    cmbdb->setObjectName(QString::fromUtf8("cmbdb"));
    cmbdb->setGeometry(QRect(130, 30, 251, 29));
    mainwidget->addWidget(page_2);

    retranslateUi(newdbfrm);

    QSize size(431, 234);
    size = size.expandedTo(newdbfrm->minimumSizeHint());
    newdbfrm->resize(size);

    QObject::connect(btncancel, SIGNAL(released()), newdbfrm, SLOT(reject()));
    QObject::connect(btncancel_2, SIGNAL(released()), newdbfrm, SLOT(reject()));
    QObject::connect(btnfinish, SIGNAL(released()), newdbfrm, SLOT(accept()));

    mainwidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(newdbfrm);
    } // setupUi

    void retranslateUi(QDialog *newdbfrm)
    {
    newdbfrm->setWindowTitle(QApplication::translate("newdbfrm", "New connection...", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("newdbfrm", "Password", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("newdbfrm", "Username:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("newdbfrm", "Host:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("newdbfrm", "Connect to database:", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("newdbfrm", "&Cancel", 0, QApplication::UnicodeUTF8));
    btnnext->setText(QApplication::translate("newdbfrm", "&Next", 0, QApplication::UnicodeUTF8));
    txtport->setText(QApplication::translate("newdbfrm", "3306", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("newdbfrm", "Port:", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("newdbfrm", "Database:", 0, QApplication::UnicodeUTF8));
    btnfinish->setText(QApplication::translate("newdbfrm", "&Finish", 0, QApplication::UnicodeUTF8));
    btncancel_2->setText(QApplication::translate("newdbfrm", "&Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(newdbfrm);
    } // retranslateUi

};

namespace Ui {
    class newdbfrm: public Ui_newdbfrm {};
} // namespace Ui

#endif // UI_NEWDBFRM_H
