/********************************************************************************
** Form generated from reading ui file 'ordersfrm.ui'
**
** Created: Thu Apr 5 22:13:13 2007
**      by: Qt User Interface Compiler version 4.3.0beta
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ORDERSFRM_H
#define UI_ORDERSFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class Ui_ordersfrm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *btnadd;
    QPushButton *btnedit;
    QPushButton *btndelete;
    QPushButton *btncompleted;
    QHBoxLayout *hboxLayout1;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *lbluser;
    QProgressBar *progbar;
    QTreeWidget *treemain;
    QTreeWidget *treeindex;

    void setupUi(QWidget *ordersfrm)
    {
    if (ordersfrm->objectName().isEmpty())
        ordersfrm->setObjectName(QString::fromUtf8("ordersfrm"));
    QSize size(887, 552);
    size = size.expandedTo(ordersfrm->minimumSizeHint());
    ordersfrm->resize(size);
    ordersfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/kfm.png")));
    gridLayout = new QGridLayout(ordersfrm);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout->setMargin(9);
#endif
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout->setMargin(0);
#endif
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(ordersfrm);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    lineEdit = new QLineEdit(ordersfrm);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    hboxLayout->addWidget(lineEdit);

    label_2 = new QLabel(ordersfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout->addWidget(label_2);

    comboBox = new QComboBox(ordersfrm);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));

    hboxLayout->addWidget(comboBox);


    hboxLayout->addItem(new QSpacerItem(241, 26, QSizePolicy::Expanding, QSizePolicy::Minimum));

    btnadd = new QPushButton(ordersfrm);
    btnadd->setObjectName(QString::fromUtf8("btnadd"));
    btnadd->setIcon(QIcon(QString::fromUtf8(":/images/images/filenew.png")));

    hboxLayout->addWidget(btnadd);

    btnedit = new QPushButton(ordersfrm);
    btnedit->setObjectName(QString::fromUtf8("btnedit"));
    btnedit->setIcon(QIcon(QString::fromUtf8(":/images/images/kfind.png")));

    hboxLayout->addWidget(btnedit);

    btndelete = new QPushButton(ordersfrm);
    btndelete->setObjectName(QString::fromUtf8("btndelete"));
    btndelete->setIcon(QIcon(QString::fromUtf8(":/images/images/editdelete.png")));

    hboxLayout->addWidget(btndelete);

    btncompleted = new QPushButton(ordersfrm);
    btncompleted->setObjectName(QString::fromUtf8("btncompleted"));
    btncompleted->setIcon(QIcon(QString::fromUtf8(":/images/images/button_ok.png")));

    hboxLayout->addWidget(btncompleted);


    gridLayout->addLayout(hboxLayout, 0, 0, 1, 2);

    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    pushButton = new QPushButton(ordersfrm);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    hboxLayout1->addWidget(pushButton);

    label_3 = new QLabel(ordersfrm);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout1->addWidget(label_3);

    lbluser = new QLabel(ordersfrm);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));

    hboxLayout1->addWidget(lbluser);


    hboxLayout1->addItem(new QSpacerItem(271, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    progbar = new QProgressBar(ordersfrm);
    progbar->setObjectName(QString::fromUtf8("progbar"));
    progbar->setMaximumSize(QSize(16777215, 20));
    progbar->setValue(24);
    progbar->setOrientation(Qt::Horizontal);

    hboxLayout1->addWidget(progbar);


    gridLayout->addLayout(hboxLayout1, 2, 0, 1, 2);

    treemain = new QTreeWidget(ordersfrm);
    treemain->setObjectName(QString::fromUtf8("treemain"));
    treemain->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout->addWidget(treemain, 1, 1, 1, 1);

    treeindex = new QTreeWidget(ordersfrm);
    treeindex->setObjectName(QString::fromUtf8("treeindex"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(treeindex->sizePolicy().hasHeightForWidth());
    treeindex->setSizePolicy(sizePolicy);
    treeindex->setMinimumSize(QSize(211, 441));
    treeindex->setMaximumSize(QSize(256, 16777215));

    gridLayout->addWidget(treeindex, 1, 0, 1, 1);


    retranslateUi(ordersfrm);

    QMetaObject::connectSlotsByName(ordersfrm);
    } // setupUi

    void retranslateUi(QWidget *ordersfrm)
    {
    ordersfrm->setWindowTitle(QApplication::translate("ordersfrm", "Purchase orders...", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ordersfrm", "Search:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ordersfrm", "Field:", 0, QApplication::UnicodeUTF8));
    comboBox->clear();
    comboBox->addItem(QApplication::translate("ordersfrm", "Order #", 0, QApplication::UnicodeUTF8));
    comboBox->addItem(QApplication::translate("ordersfrm", "Supplier", 0, QApplication::UnicodeUTF8));
    comboBox->addItem(QApplication::translate("ordersfrm", "Description", 0, QApplication::UnicodeUTF8));
    comboBox->addItem(QApplication::translate("ordersfrm", "Date", 0, QApplication::UnicodeUTF8));
    btnadd->setText(QString());
    btnedit->setText(QString());
    btndelete->setText(QString());
    btncompleted->setText(QString());
    pushButton->setText(QApplication::translate("ordersfrm", "&Close", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ordersfrm", "User:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("ordersfrm", "-", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(0, QApplication::translate("ordersfrm", "-", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(1, QApplication::translate("ordersfrm", "Date", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(2, QApplication::translate("ordersfrm", "Label", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(3, QApplication::translate("ordersfrm", "Description", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(4, QApplication::translate("ordersfrm", "Quantity", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(5, QApplication::translate("ordersfrm", "Price", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(6, QApplication::translate("ordersfrm", "Order nr", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(7, QApplication::translate("ordersfrm", "Ordered by", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(8, QApplication::translate("ordersfrm", "Stock", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(9, QApplication::translate("ordersfrm", "Suppliers", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(10, QApplication::translate("ordersfrm", "Comments", 0, QApplication::UnicodeUTF8));
    treeindex->headerItem()->setText(0, QApplication::translate("ordersfrm", "State", 0, QApplication::UnicodeUTF8));
    treeindex->headerItem()->setText(1, QApplication::translate("ordersfrm", "Quantity", 0, QApplication::UnicodeUTF8));
    treeindex->headerItem()->setText(2, QApplication::translate("ordersfrm", "sort", 0, QApplication::UnicodeUTF8));
    treeindex->clear();

    QTreeWidgetItem *__item = new QTreeWidgetItem(treeindex);
    __item->setText(0, QApplication::translate("ordersfrm", "New orders", 0, QApplication::UnicodeUTF8));
    __item->setText(1, QApplication::translate("ordersfrm", "1", 0, QApplication::UnicodeUTF8));
    __item->setText(2, QApplication::translate("ordersfrm", "0", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item1 = new QTreeWidgetItem(treeindex);
    __item1->setText(0, QApplication::translate("ordersfrm", "Pending orders", 0, QApplication::UnicodeUTF8));
    __item1->setText(1, QApplication::translate("ordersfrm", "2", 0, QApplication::UnicodeUTF8));
    __item1->setText(2, QApplication::translate("ordersfrm", "1", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item2 = new QTreeWidgetItem(treeindex);
    __item2->setText(0, QApplication::translate("ordersfrm", "Delivered orders", 0, QApplication::UnicodeUTF8));
    __item2->setText(1, QApplication::translate("ordersfrm", "3", 0, QApplication::UnicodeUTF8));
    __item2->setText(2, QApplication::translate("ordersfrm", "2", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item3 = new QTreeWidgetItem(treeindex);
    __item3->setText(0, QApplication::translate("ordersfrm", "Archive", 0, QApplication::UnicodeUTF8));
    __item3->setText(1, QApplication::translate("ordersfrm", "4", 0, QApplication::UnicodeUTF8));
    __item3->setText(2, QApplication::translate("ordersfrm", "3", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ordersfrm);
    } // retranslateUi

};

namespace Ui {
    class ordersfrm: public Ui_ordersfrm {};
} // namespace Ui

#endif // UI_ORDERSFRM_H
