/********************************************************************************
** Form generated from reading ui file 'docopenfrm.ui'
**
** Created: Thu Mar 1 12:03:11 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DOCOPENFRM_H
#define UI_DOCOPENFRM_H

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

class Ui_docopenfrm
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem;
    QGridLayout *gridLayout2;
    QPushButton *btnclearsearch;
    QLabel *label_2;
    QLineEdit *txtsearch;
    QPushButton *btnsearch;
    QPushButton *btnaddr;
    QComboBox *cmbsearchrow;
    QLabel *label;
    QGridLayout *gridLayout3;
    QPushButton *btnprint;
    QSpacerItem *spacerItem1;
    QPushButton *btnedit;
    QPushButton *btnnew;
    QPushButton *btndelete;
    QTreeWidget *treeindex;
    QHBoxLayout *hboxLayout;
    QPushButton *btnclose;
    QSpacerItem *spacerItem2;
    QLabel *label_3;
    QLabel *lbluser;
    QSpacerItem *spacerItem3;
    QProgressBar *progbar;
    QSpacerItem *spacerItem4;
    QPushButton *btnopen;
    QTreeWidget *treemain;

    void setupUi(QWidget *docopenfrm)
    {
    docopenfrm->setObjectName(QString::fromUtf8("docopenfrm"));
    docopenfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/wordprocessing.png")));
    gridLayout = new QGridLayout(docopenfrm);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout1 = new QGridLayout();
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(0);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    spacerItem = new QSpacerItem(42, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem, 0, 1, 1, 1);

    gridLayout2 = new QGridLayout();
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(0);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    btnclearsearch = new QPushButton(docopenfrm);
    btnclearsearch->setObjectName(QString::fromUtf8("btnclearsearch"));
    btnclearsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/kill.png")));

    gridLayout2->addWidget(btnclearsearch, 0, 6, 1, 1);

    label_2 = new QLabel(docopenfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout2->addWidget(label_2, 0, 2, 1, 1);

    txtsearch = new QLineEdit(docopenfrm);
    txtsearch->setObjectName(QString::fromUtf8("txtsearch"));
    txtsearch->setMinimumSize(QSize(0, 22));
    txtsearch->setMaximumSize(QSize(16777215, 22));

    gridLayout2->addWidget(txtsearch, 0, 3, 1, 1);

    btnsearch = new QPushButton(docopenfrm);
    btnsearch->setObjectName(QString::fromUtf8("btnsearch"));
    btnsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));

    gridLayout2->addWidget(btnsearch, 0, 5, 1, 1);

    btnaddr = new QPushButton(docopenfrm);
    btnaddr->setObjectName(QString::fromUtf8("btnaddr"));
    btnaddr->setIcon(QIcon(QString::fromUtf8(":/images/images/contents.png")));

    gridLayout2->addWidget(btnaddr, 0, 4, 1, 1);

    cmbsearchrow = new QComboBox(docopenfrm);
    cmbsearchrow->setObjectName(QString::fromUtf8("cmbsearchrow"));

    gridLayout2->addWidget(cmbsearchrow, 0, 1, 1, 1);

    label = new QLabel(docopenfrm);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout2->addWidget(label, 0, 0, 1, 1);


    gridLayout1->addLayout(gridLayout2, 0, 0, 1, 1);

    gridLayout3 = new QGridLayout();
    gridLayout3->setSpacing(6);
    gridLayout3->setMargin(0);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    btnprint = new QPushButton(docopenfrm);
    btnprint->setObjectName(QString::fromUtf8("btnprint"));
    btnprint->setMinimumSize(QSize(41, 41));
    btnprint->setMaximumSize(QSize(41, 41));
    btnprint->setIcon(QIcon(QString::fromUtf8(":/images/images/fileprint.png")));
    btnprint->setIconSize(QSize(32, 32));

    gridLayout3->addWidget(btnprint, 0, 4, 1, 1);

    spacerItem1 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    gridLayout3->addItem(spacerItem1, 0, 3, 1, 1);

    btnedit = new QPushButton(docopenfrm);
    btnedit->setObjectName(QString::fromUtf8("btnedit"));
    btnedit->setMinimumSize(QSize(41, 41));
    btnedit->setMaximumSize(QSize(41, 41));
    btnedit->setIcon(QIcon(QString::fromUtf8(":/images/images/kfind.png")));
    btnedit->setIconSize(QSize(32, 32));

    gridLayout3->addWidget(btnedit, 0, 1, 1, 1);

    btnnew = new QPushButton(docopenfrm);
    btnnew->setObjectName(QString::fromUtf8("btnnew"));
    btnnew->setMinimumSize(QSize(41, 41));
    btnnew->setMaximumSize(QSize(41, 41));
    btnnew->setIcon(QIcon(QString::fromUtf8(":/images/images/filenew.png")));
    btnnew->setIconSize(QSize(32, 32));

    gridLayout3->addWidget(btnnew, 0, 0, 1, 1);

    btndelete = new QPushButton(docopenfrm);
    btndelete->setObjectName(QString::fromUtf8("btndelete"));
    btndelete->setMinimumSize(QSize(41, 41));
    btndelete->setMaximumSize(QSize(41, 41));
    btndelete->setIcon(QIcon(QString::fromUtf8(":/images/images/editdelete.png")));
    btndelete->setIconSize(QSize(32, 32));

    gridLayout3->addWidget(btndelete, 0, 2, 1, 1);


    gridLayout1->addLayout(gridLayout3, 0, 2, 1, 1);


    gridLayout->addLayout(gridLayout1, 0, 0, 1, 2);

    treeindex = new QTreeWidget(docopenfrm);
    treeindex->setObjectName(QString::fromUtf8("treeindex"));
    treeindex->setMaximumSize(QSize(221, 16777215));

    gridLayout->addWidget(treeindex, 1, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    btnclose = new QPushButton(docopenfrm);
    btnclose->setObjectName(QString::fromUtf8("btnclose"));

    hboxLayout->addWidget(btnclose);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem2);

    label_3 = new QLabel(docopenfrm);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout->addWidget(label_3);

    lbluser = new QLabel(docopenfrm);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));

    hboxLayout->addWidget(lbluser);

    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem3);

    progbar = new QProgressBar(docopenfrm);
    progbar->setObjectName(QString::fromUtf8("progbar"));
    progbar->setMinimumSize(QSize(250, 19));
    progbar->setMaximumSize(QSize(250, 19));
    progbar->setValue(0);
    progbar->setOrientation(Qt::Horizontal);

    hboxLayout->addWidget(progbar);

    spacerItem4 = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem4);

    btnopen = new QPushButton(docopenfrm);
    btnopen->setObjectName(QString::fromUtf8("btnopen"));

    hboxLayout->addWidget(btnopen);


    gridLayout->addLayout(hboxLayout, 2, 0, 1, 2);

    treemain = new QTreeWidget(docopenfrm);
    treemain->setObjectName(QString::fromUtf8("treemain"));

    gridLayout->addWidget(treemain, 1, 1, 1, 1);


    retranslateUi(docopenfrm);

    QSize size(913, 554);
    size = size.expandedTo(docopenfrm->minimumSizeHint());
    docopenfrm->resize(size);


    QMetaObject::connectSlotsByName(docopenfrm);
    } // setupUi

    void retranslateUi(QWidget *docopenfrm)
    {
    docopenfrm->setWindowTitle(QApplication::translate("docopenfrm", "Open document...", 0, QApplication::UnicodeUTF8));
    btnclearsearch->setText(QString());
    label_2->setText(QApplication::translate("docopenfrm", "Text:", 0, QApplication::UnicodeUTF8));
    btnsearch->setText(QString());
    btnaddr->setText(QString());
    cmbsearchrow->clear();
    cmbsearchrow->addItem(QApplication::translate("docopenfrm", "Client", 0, QApplication::UnicodeUTF8));
    cmbsearchrow->addItem(QApplication::translate("docopenfrm", "Document-ID", 0, QApplication::UnicodeUTF8));
    cmbsearchrow->addItem(QApplication::translate("docopenfrm", "Date", 0, QApplication::UnicodeUTF8));
    cmbsearchrow->addItem(QApplication::translate("docopenfrm", "Positions", 0, QApplication::UnicodeUTF8));
    cmbsearchrow->addItem(QApplication::translate("docopenfrm", "Comments", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("docopenfrm", "Search in:", 0, QApplication::UnicodeUTF8));
    btnprint->setText(QString());
    btnedit->setText(QString());
    btnnew->setText(QString());
    btndelete->setText(QString());
    treeindex->headerItem()->setText(0, QApplication::translate("docopenfrm", "Documents", 0, QApplication::UnicodeUTF8));
    treeindex->headerItem()->setText(1, QApplication::translate("docopenfrm", "name", 0, QApplication::UnicodeUTF8));
    treeindex->headerItem()->setText(2, QApplication::translate("docopenfrm", "sort", 0, QApplication::UnicodeUTF8));
    btnclose->setText(QApplication::translate("docopenfrm", "&Close", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("docopenfrm", "User:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("docopenfrm", "-", 0, QApplication::UnicodeUTF8));
    btnopen->setText(QApplication::translate("docopenfrm", "&Open", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(0, QApplication::translate("docopenfrm", "ID", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(1, QApplication::translate("docopenfrm", "Document ID", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(2, QApplication::translate("docopenfrm", "Date", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(3, QApplication::translate("docopenfrm", "Customer", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(4, QApplication::translate("docopenfrm", "Amount", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(5, QApplication::translate("docopenfrm", "Discount", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(6, QApplication::translate("docopenfrm", "Comments", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(7, QApplication::translate("docopenfrm", "ClientID", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(8, QApplication::translate("docopenfrm", "ClientAddr", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(docopenfrm);
    } // retranslateUi

};

namespace Ui {
    class docopenfrm: public Ui_docopenfrm {};
} // namespace Ui

#endif // UI_DOCOPENFRM_H
