/********************************************************************************
** Form generated from reading ui file 'invfrm.ui'
**
** Created: Thu Mar 1 12:03:11 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INVFRM_H
#define UI_INVFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

class Ui_invfrm
{
public:
    QGridLayout *gridLayout;
    QTableWidget *maintab;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem;
    QPushButton *btncomments;
    QPushButton *btnnew;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QLabel *label;
    QPushButton *btnsave;
    QSpacerItem *spacerItem3;
    QComboBox *cmbinv;
    QPushButton *btncomplete;
    QPushButton *btnprint;
    QGridLayout *gridLayout2;
    QLabel *label_2;
    QSpacerItem *spacerItem4;
    QProgressBar *progbar;
    QLabel *lbluser;
    QSpacerItem *spacerItem5;
    QPushButton *btnclose;

    void setupUi(QWidget *invfrm)
    {
    invfrm->setObjectName(QString::fromUtf8("invfrm"));
    invfrm->setMaximumSize(QSize(16777215, 16777215));
    invfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/kfm.png")));
    gridLayout = new QGridLayout(invfrm);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    maintab = new QTableWidget(invfrm);
    maintab->setObjectName(QString::fromUtf8("maintab"));

    gridLayout->addWidget(maintab, 1, 0, 1, 1);

    gridLayout1 = new QGridLayout();
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(0);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    spacerItem = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem, 0, 4, 1, 1);

    btncomments = new QPushButton(invfrm);
    btncomments->setObjectName(QString::fromUtf8("btncomments"));
    btncomments->setIcon(QIcon(QString::fromUtf8(":/images/images/xclipboard.png")));
    btncomments->setIconSize(QSize(22, 22));

    gridLayout1->addWidget(btncomments, 0, 3, 1, 1);

    btnnew = new QPushButton(invfrm);
    btnnew->setObjectName(QString::fromUtf8("btnnew"));
    btnnew->setIcon(QIcon(QString::fromUtf8(":/images/images/filenew.png")));
    btnnew->setIconSize(QSize(22, 22));

    gridLayout1->addWidget(btnnew, 0, 5, 1, 1);

    spacerItem1 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem1, 0, 2, 1, 1);

    spacerItem2 = new QSpacerItem(21, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem2, 0, 9, 1, 1);

    label = new QLabel(invfrm);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout1->addWidget(label, 0, 0, 1, 1);

    btnsave = new QPushButton(invfrm);
    btnsave->setObjectName(QString::fromUtf8("btnsave"));
    btnsave->setIcon(QIcon(QString::fromUtf8(":/images/images/filesave.png")));
    btnsave->setIconSize(QSize(22, 22));

    gridLayout1->addWidget(btnsave, 0, 6, 1, 1);

    spacerItem3 = new QSpacerItem(21, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem3, 0, 7, 1, 1);

    cmbinv = new QComboBox(invfrm);
    cmbinv->setObjectName(QString::fromUtf8("cmbinv"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(cmbinv->sizePolicy().hasHeightForWidth());
    cmbinv->setSizePolicy(sizePolicy);
    cmbinv->setMinimumSize(QSize(231, 22));
    cmbinv->setMaximumSize(QSize(16777215, 22));

    gridLayout1->addWidget(cmbinv, 0, 1, 1, 1);

    btncomplete = new QPushButton(invfrm);
    btncomplete->setObjectName(QString::fromUtf8("btncomplete"));
    btncomplete->setIcon(QIcon(QString::fromUtf8(":/images/images/button_ok.png")));
    btncomplete->setIconSize(QSize(22, 22));

    gridLayout1->addWidget(btncomplete, 0, 10, 1, 1);

    btnprint = new QPushButton(invfrm);
    btnprint->setObjectName(QString::fromUtf8("btnprint"));
    btnprint->setIcon(QIcon(QString::fromUtf8(":/images/images/fileprint.png")));
    btnprint->setIconSize(QSize(22, 22));

    gridLayout1->addWidget(btnprint, 0, 8, 1, 1);


    gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);

    gridLayout2 = new QGridLayout();
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(0);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    label_2 = new QLabel(invfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout2->addWidget(label_2, 0, 2, 1, 1);

    spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    gridLayout2->addItem(spacerItem4, 0, 1, 1, 1);

    progbar = new QProgressBar(invfrm);
    progbar->setObjectName(QString::fromUtf8("progbar"));
    progbar->setMaximumSize(QSize(265, 18));
    progbar->setValue(0);
    progbar->setOrientation(Qt::Horizontal);

    gridLayout2->addWidget(progbar, 0, 5, 1, 1);

    lbluser = new QLabel(invfrm);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));

    gridLayout2->addWidget(lbluser, 0, 3, 1, 1);

    spacerItem5 = new QSpacerItem(181, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout2->addItem(spacerItem5, 0, 4, 1, 1);

    btnclose = new QPushButton(invfrm);
    btnclose->setObjectName(QString::fromUtf8("btnclose"));

    gridLayout2->addWidget(btnclose, 0, 0, 1, 1);


    gridLayout->addLayout(gridLayout2, 2, 0, 1, 1);


    retranslateUi(invfrm);

    QSize size(730, 659);
    size = size.expandedTo(invfrm->minimumSizeHint());
    invfrm->resize(size);

    QObject::connect(btnclose, SIGNAL(released()), invfrm, SLOT(close()));

    QMetaObject::connectSlotsByName(invfrm);
    } // setupUi

    void retranslateUi(QWidget *invfrm)
    {
    invfrm->setWindowTitle(QApplication::translate("invfrm", "Inventory...", 0, QApplication::UnicodeUTF8));
    if (maintab->columnCount() < 10)
        maintab->setColumnCount(10);

    QTableWidgetItem *__colItem = new QTableWidgetItem();
    __colItem->setText(QApplication::translate("invfrm", "ID", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(0, __colItem);

    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    __colItem1->setText(QApplication::translate("invfrm", "Stock ID", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(1, __colItem1);

    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    __colItem2->setText(QApplication::translate("invfrm", "Def.", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(2, __colItem2);

    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    __colItem3->setText(QApplication::translate("invfrm", "Description", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(3, __colItem3);

    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    __colItem4->setText(QApplication::translate("invfrm", "Quantity", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(4, __colItem4);

    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    __colItem5->setText(QApplication::translate("invfrm", "Purchase Price", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(5, __colItem5);

    QTableWidgetItem *__colItem6 = new QTableWidgetItem();
    __colItem6->setText(QApplication::translate("invfrm", "Resell Price", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(6, __colItem6);

    QTableWidgetItem *__colItem7 = new QTableWidgetItem();
    __colItem7->setText(QApplication::translate("invfrm", "Actual Price", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(7, __colItem7);

    QTableWidgetItem *__colItem8 = new QTableWidgetItem();
    __colItem8->setText(QApplication::translate("invfrm", "New quantity", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(8, __colItem8);

    QTableWidgetItem *__colItem9 = new QTableWidgetItem();
    __colItem9->setText(QApplication::translate("invfrm", "Comments", 0, QApplication::UnicodeUTF8));
    maintab->setHorizontalHeaderItem(9, __colItem9);
    btncomments->setText(QString());
    label->setText(QApplication::translate("invfrm", "Inventory:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("invfrm", "User:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("invfrm", "-", 0, QApplication::UnicodeUTF8));
    btnclose->setText(QApplication::translate("invfrm", "&Close", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(invfrm);
    } // retranslateUi

};

namespace Ui {
    class invfrm: public Ui_invfrm {};
} // namespace Ui

#endif // UI_INVFRM_H
