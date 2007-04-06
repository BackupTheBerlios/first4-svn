/********************************************************************************
** Form generated from reading ui file 'datafrm.ui'
**
** Created: Thu Apr 5 22:13:13 2007
**      by: Qt User Interface Compiler version 4.3.0beta
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DATAFRM_H
#define UI_DATAFRM_H

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
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class Ui_datafrm
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *mainwidget;
    QWidget *page;
    QGridLayout *gridLayout1;
    QTreeWidget *maintree;
    QWidget *page_2;
    QGridLayout *gridLayout2;
    QTableWidget *maintable;
    QHBoxLayout *hboxLayout;
    QPushButton *btnclose;
    QLabel *label;
    QLabel *lbluser;
    QProgressBar *progbar;
    QPushButton *btnsave;
    QHBoxLayout *hboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *label_2;
    QComboBox *cmbdata;
    QLineEdit *txtsearch;
    QPushButton *btnsearch;
    QPushButton *btnclear;
    QHBoxLayout *hboxLayout3;
    QPushButton *btnnew;
    QPushButton *btnedit;
    QPushButton *btndelete;
    QPushButton *btnprint;
    QPushButton *btntransfer;

    void setupUi(QWidget *datafrm)
    {
    if (datafrm->objectName().isEmpty())
        datafrm->setObjectName(QString::fromUtf8("datafrm"));
    QSize size(875, 657);
    size = size.expandedTo(datafrm->minimumSizeHint());
    datafrm->resize(size);
    datafrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/kfm.png")));
    gridLayout = new QGridLayout(datafrm);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout->setMargin(9);
#endif
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    mainwidget = new QStackedWidget(datafrm);
    mainwidget->setObjectName(QString::fromUtf8("mainwidget"));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    gridLayout1 = new QGridLayout(page);
#ifndef Q_OS_MAC
    gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout1->setMargin(9);
#endif
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    maintree = new QTreeWidget(page);
    maintree->setObjectName(QString::fromUtf8("maintree"));
    maintree->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout1->addWidget(maintree, 0, 0, 1, 1);

    mainwidget->addWidget(page);
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    gridLayout2 = new QGridLayout(page_2);
#ifndef Q_OS_MAC
    gridLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout2->setMargin(9);
#endif
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    maintable = new QTableWidget(page_2);
    maintable->setObjectName(QString::fromUtf8("maintable"));
    maintable->setContextMenuPolicy(Qt::CustomContextMenu);
    maintable->setAlternatingRowColors(true);
    maintable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    maintable->setSelectionBehavior(QAbstractItemView::SelectItems);

    gridLayout2->addWidget(maintable, 0, 0, 1, 1);

    mainwidget->addWidget(page_2);

    gridLayout->addWidget(mainwidget, 1, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    btnclose = new QPushButton(datafrm);
    btnclose->setObjectName(QString::fromUtf8("btnclose"));

    hboxLayout->addWidget(btnclose);


    hboxLayout->addItem(new QSpacerItem(31, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));

    label = new QLabel(datafrm);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    lbluser = new QLabel(datafrm);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(lbluser->sizePolicy().hasHeightForWidth());
    lbluser->setSizePolicy(sizePolicy);

    hboxLayout->addWidget(lbluser);


    hboxLayout->addItem(new QSpacerItem(371, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    progbar = new QProgressBar(datafrm);
    progbar->setObjectName(QString::fromUtf8("progbar"));
    sizePolicy.setHeightForWidth(progbar->sizePolicy().hasHeightForWidth());
    progbar->setSizePolicy(sizePolicy);
    progbar->setMinimumSize(QSize(151, 0));
    progbar->setMaximumSize(QSize(151, 19));
    progbar->setValue(24);
    progbar->setOrientation(Qt::Horizontal);

    hboxLayout->addWidget(progbar);


    hboxLayout->addItem(new QSpacerItem(81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    btnsave = new QPushButton(datafrm);
    btnsave->setObjectName(QString::fromUtf8("btnsave"));

    hboxLayout->addWidget(btnsave);


    gridLayout->addLayout(hboxLayout, 2, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout2->setMargin(0);
#endif
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label_2 = new QLabel(datafrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setMaximumSize(QSize(16777215, 21));

    hboxLayout2->addWidget(label_2);

    cmbdata = new QComboBox(datafrm);
    cmbdata->setObjectName(QString::fromUtf8("cmbdata"));
    cmbdata->setMinimumSize(QSize(181, 0));
    cmbdata->setMaximumSize(QSize(16777215, 22));

    hboxLayout2->addWidget(cmbdata);

    txtsearch = new QLineEdit(datafrm);
    txtsearch->setObjectName(QString::fromUtf8("txtsearch"));
    txtsearch->setMaximumSize(QSize(16777215, 22));

    hboxLayout2->addWidget(txtsearch);

    btnsearch = new QPushButton(datafrm);
    btnsearch->setObjectName(QString::fromUtf8("btnsearch"));
    sizePolicy.setHeightForWidth(btnsearch->sizePolicy().hasHeightForWidth());
    btnsearch->setSizePolicy(sizePolicy);
    btnsearch->setMaximumSize(QSize(21, 21));
    btnsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));

    hboxLayout2->addWidget(btnsearch);

    btnclear = new QPushButton(datafrm);
    btnclear->setObjectName(QString::fromUtf8("btnclear"));
    sizePolicy.setHeightForWidth(btnclear->sizePolicy().hasHeightForWidth());
    btnclear->setSizePolicy(sizePolicy);
    btnclear->setMaximumSize(QSize(21, 21));
    btnclear->setIcon(QIcon(QString::fromUtf8(":/images/images/kill.png")));

    hboxLayout2->addWidget(btnclear);


    hboxLayout1->addLayout(hboxLayout2);


    hboxLayout1->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout3->setSpacing(6);
#endif
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    btnnew = new QPushButton(datafrm);
    btnnew->setObjectName(QString::fromUtf8("btnnew"));
    sizePolicy.setHeightForWidth(btnnew->sizePolicy().hasHeightForWidth());
    btnnew->setSizePolicy(sizePolicy);
    btnnew->setMaximumSize(QSize(31, 31));
    btnnew->setIcon(QIcon(QString::fromUtf8(":/images/images/filenew.png")));
    btnnew->setIconSize(QSize(24, 24));

    hboxLayout3->addWidget(btnnew);

    btnedit = new QPushButton(datafrm);
    btnedit->setObjectName(QString::fromUtf8("btnedit"));
    sizePolicy.setHeightForWidth(btnedit->sizePolicy().hasHeightForWidth());
    btnedit->setSizePolicy(sizePolicy);
    btnedit->setMaximumSize(QSize(31, 31));
    btnedit->setIcon(QIcon(QString::fromUtf8(":/images/images/kfind.png")));
    btnedit->setIconSize(QSize(24, 24));

    hboxLayout3->addWidget(btnedit);

    btndelete = new QPushButton(datafrm);
    btndelete->setObjectName(QString::fromUtf8("btndelete"));
    sizePolicy.setHeightForWidth(btndelete->sizePolicy().hasHeightForWidth());
    btndelete->setSizePolicy(sizePolicy);
    btndelete->setMaximumSize(QSize(31, 31));
    btndelete->setIcon(QIcon(QString::fromUtf8(":/images/images/editdelete.png")));
    btndelete->setIconSize(QSize(24, 24));

    hboxLayout3->addWidget(btndelete);


    hboxLayout3->addItem(new QSpacerItem(16, 31, QSizePolicy::Fixed, QSizePolicy::Minimum));

    btnprint = new QPushButton(datafrm);
    btnprint->setObjectName(QString::fromUtf8("btnprint"));
    sizePolicy.setHeightForWidth(btnprint->sizePolicy().hasHeightForWidth());
    btnprint->setSizePolicy(sizePolicy);
    btnprint->setMaximumSize(QSize(31, 31));
    btnprint->setIcon(QIcon(QString::fromUtf8(":/images/images/fileprint.png")));
    btnprint->setIconSize(QSize(24, 24));

    hboxLayout3->addWidget(btnprint);


    hboxLayout3->addItem(new QSpacerItem(16, 31, QSizePolicy::Fixed, QSizePolicy::Minimum));

    btntransfer = new QPushButton(datafrm);
    btntransfer->setObjectName(QString::fromUtf8("btntransfer"));
    sizePolicy.setHeightForWidth(btntransfer->sizePolicy().hasHeightForWidth());
    btntransfer->setSizePolicy(sizePolicy);
    btntransfer->setMaximumSize(QSize(31, 31));
    btntransfer->setIcon(QIcon(QString::fromUtf8(":/images/images/impexp.png")));
    btntransfer->setIconSize(QSize(24, 24));

    hboxLayout3->addWidget(btntransfer);


    hboxLayout1->addLayout(hboxLayout3);


    gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);


    retranslateUi(datafrm);
    QObject::connect(btnclose, SIGNAL(released()), datafrm, SLOT(close()));

    mainwidget->setCurrentIndex(1);


    QMetaObject::connectSlotsByName(datafrm);
    } // setupUi

    void retranslateUi(QWidget *datafrm)
    {
    datafrm->setWindowTitle(QApplication::translate("datafrm", "Stock / Datatables", 0, QApplication::UnicodeUTF8));
    btnclose->setText(QApplication::translate("datafrm", "&Close", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("datafrm", "User:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("datafrm", "-", 0, QApplication::UnicodeUTF8));
    btnsave->setText(QApplication::translate("datafrm", "&Save", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("datafrm", "Datatable:", 0, QApplication::UnicodeUTF8));
    btnsearch->setText(QString());
    btnnew->setText(QString());
    btnedit->setText(QString());
    btndelete->setText(QString());
    btnprint->setText(QString());
    btntransfer->setText(QString());
    btntransfer->setShortcut(QApplication::translate("datafrm", "S", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(datafrm);
    } // retranslateUi

};

namespace Ui {
    class datafrm: public Ui_datafrm {};
} // namespace Ui

#endif // UI_DATAFRM_H
