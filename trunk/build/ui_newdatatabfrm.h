/********************************************************************************
** Form generated from reading ui file 'newdatatabfrm.ui'
**
** Created: Thu Mar 1 12:03:10 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NEWDATATABFRM_H
#define UI_NEWDATATABFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

class Ui_newdatatabfrm
{
public:
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QPushButton *btncreate;
    QPushButton *btncance;
    QGroupBox *groupBox;
    QRadioButton *rdbstock;
    QRadioButton *rdbiecode;
    QRadioButton *rdbcustom;
    QGroupBox *grpcols;
    QListWidget *listcols;
    QPushButton *btnadd;
    QPushButton *btnremove;
    QPushButton *btnup;
    QPushButton *btndown;
    QLineEdit *txtname;

    void setupUi(QDialog *newdatatabfrm)
    {
    newdatatabfrm->setObjectName(QString::fromUtf8("newdatatabfrm"));
    newdatatabfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    newdatatabfrm->setSizeGripEnabled(false);
    label_2 = new QLabel(newdatatabfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 50, 71, 17));
    label = new QLabel(newdatatabfrm);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 10, 71, 17));
    label_3 = new QLabel(newdatatabfrm);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(10, 120, 71, 17));
    btncreate = new QPushButton(newdatatabfrm);
    btncreate->setObjectName(QString::fromUtf8("btncreate"));
    btncreate->setGeometry(QRect(320, 290, 75, 27));
    btncance = new QPushButton(newdatatabfrm);
    btncance->setObjectName(QString::fromUtf8("btncance"));
    btncance->setGeometry(QRect(10, 290, 75, 27));
    groupBox = new QGroupBox(newdatatabfrm);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(90, 40, 301, 61));
    rdbstock = new QRadioButton(groupBox);
    rdbstock->setObjectName(QString::fromUtf8("rdbstock"));
    rdbstock->setGeometry(QRect(10, 10, 98, 23));
    rdbiecode = new QRadioButton(groupBox);
    rdbiecode->setObjectName(QString::fromUtf8("rdbiecode"));
    rdbiecode->setGeometry(QRect(140, 10, 98, 23));
    rdbcustom = new QRadioButton(groupBox);
    rdbcustom->setObjectName(QString::fromUtf8("rdbcustom"));
    rdbcustom->setGeometry(QRect(10, 30, 98, 23));
    grpcols = new QGroupBox(newdatatabfrm);
    grpcols->setObjectName(QString::fromUtf8("grpcols"));
    grpcols->setGeometry(QRect(90, 110, 301, 171));
    listcols = new QListWidget(grpcols);
    listcols->setObjectName(QString::fromUtf8("listcols"));
    listcols->setGeometry(QRect(10, 10, 241, 151));
    btnadd = new QPushButton(grpcols);
    btnadd->setObjectName(QString::fromUtf8("btnadd"));
    btnadd->setGeometry(QRect(259, 10, 31, 27));
    btnadd->setIcon(QIcon(QString::fromUtf8(":/images/images/hotlistadd.png")));
    btnremove = new QPushButton(grpcols);
    btnremove->setObjectName(QString::fromUtf8("btnremove"));
    btnremove->setGeometry(QRect(260, 50, 31, 27));
    btnremove->setIcon(QIcon(QString::fromUtf8(":/images/images/hotlistdel.png")));
    btnup = new QPushButton(grpcols);
    btnup->setObjectName(QString::fromUtf8("btnup"));
    btnup->setGeometry(QRect(260, 90, 31, 27));
    btnup->setIcon(QIcon(QString::fromUtf8(":/images/images/up.png")));
    btndown = new QPushButton(grpcols);
    btndown->setObjectName(QString::fromUtf8("btndown"));
    btndown->setGeometry(QRect(260, 130, 31, 27));
    btndown->setIcon(QIcon(QString::fromUtf8(":/images/images/down.png")));
    txtname = new QLineEdit(newdatatabfrm);
    txtname->setObjectName(QString::fromUtf8("txtname"));
    txtname->setGeometry(QRect(90, 10, 301, 23));

    retranslateUi(newdatatabfrm);

    QSize size(400, 323);
    size = size.expandedTo(newdatatabfrm->minimumSizeHint());
    newdatatabfrm->resize(size);

    QObject::connect(btncreate, SIGNAL(clicked()), newdatatabfrm, SLOT(accept()));
    QObject::connect(btncance, SIGNAL(clicked()), newdatatabfrm, SLOT(reject()));

    QMetaObject::connectSlotsByName(newdatatabfrm);
    } // setupUi

    void retranslateUi(QDialog *newdatatabfrm)
    {
    newdatatabfrm->setWindowTitle(QApplication::translate("newdatatabfrm", "New Datatable...", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("newdatatabfrm", "Type:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("newdatatabfrm", "Name:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("newdatatabfrm", "Columns:", 0, QApplication::UnicodeUTF8));
    btncreate->setText(QApplication::translate("newdatatabfrm", "&Create", 0, QApplication::UnicodeUTF8));
    btncance->setText(QApplication::translate("newdatatabfrm", "C&ancel", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QString());
    rdbstock->setText(QApplication::translate("newdatatabfrm", "Stock", 0, QApplication::UnicodeUTF8));
    rdbiecode->setText(QApplication::translate("newdatatabfrm", "IE-Codelist", 0, QApplication::UnicodeUTF8));
    rdbcustom->setText(QApplication::translate("newdatatabfrm", "Custom", 0, QApplication::UnicodeUTF8));
    grpcols->setTitle(QString());
    Q_UNUSED(newdatatabfrm);
    } // retranslateUi

};

namespace Ui {
    class newdatatabfrm: public Ui_newdatatabfrm {};
} // namespace Ui

#endif // UI_NEWDATATABFRM_H
