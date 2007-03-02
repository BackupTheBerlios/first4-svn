/********************************************************************************
** Form generated from reading ui file 'addrselectfrm.ui'
**
** Created: Thu Mar 1 12:03:11 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ADDRSELECTFRM_H
#define UI_ADDRSELECTFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class Ui_addrselectfrm
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *spacerItem;
    QLineEdit *txtsearch;
    QComboBox *cmbdir;
    QLabel *label_2;
    QLabel *label;
    QPushButton *btnsearch;
    QPushButton *btncancel;
    QPushButton *btnaccept;
    QTreeWidget *treemain;
    QProgressBar *progbar;
    QPushButton *btncancelsearch;

    void setupUi(QDialog *addrselectfrm)
    {
    addrselectfrm->setObjectName(QString::fromUtf8("addrselectfrm"));
    addrselectfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/kdmconfig.png")));
    layoutWidget = new QWidget(addrselectfrm);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(10, 10, 381, 55));
    gridLayout = new QGridLayout(layoutWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(0);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    spacerItem = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem, 0, 2, 1, 1);

    txtsearch = new QLineEdit(layoutWidget);
    txtsearch->setObjectName(QString::fromUtf8("txtsearch"));

    gridLayout->addWidget(txtsearch, 1, 1, 1, 2);

    cmbdir = new QComboBox(layoutWidget);
    cmbdir->setObjectName(QString::fromUtf8("cmbdir"));

    gridLayout->addWidget(cmbdir, 0, 1, 1, 1);

    label_2 = new QLabel(layoutWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    label = new QLabel(layoutWidget);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    btnsearch = new QPushButton(addrselectfrm);
    btnsearch->setObjectName(QString::fromUtf8("btnsearch"));
    btnsearch->setGeometry(QRect(400, 40, 21, 21));
    btnsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
    btncancel = new QPushButton(addrselectfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(10, 330, 75, 27));
    btnaccept = new QPushButton(addrselectfrm);
    btnaccept->setObjectName(QString::fromUtf8("btnaccept"));
    btnaccept->setGeometry(QRect(470, 330, 75, 27));
    treemain = new QTreeWidget(addrselectfrm);
    treemain->setObjectName(QString::fromUtf8("treemain"));
    treemain->setGeometry(QRect(10, 70, 531, 251));
    progbar = new QProgressBar(addrselectfrm);
    progbar->setObjectName(QString::fromUtf8("progbar"));
    progbar->setGeometry(QRect(200, 333, 118, 20));
    progbar->setValue(0);
    progbar->setOrientation(Qt::Horizontal);
    btncancelsearch = new QPushButton(addrselectfrm);
    btncancelsearch->setObjectName(QString::fromUtf8("btncancelsearch"));
    btncancelsearch->setGeometry(QRect(430, 40, 21, 21));
    btncancelsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/kill.png")));

    retranslateUi(addrselectfrm);

    QSize size(552, 361);
    size = size.expandedTo(addrselectfrm->minimumSizeHint());
    addrselectfrm->resize(size);

    QObject::connect(btnaccept, SIGNAL(clicked()), addrselectfrm, SLOT(accept()));
    QObject::connect(btncancel, SIGNAL(clicked()), addrselectfrm, SLOT(reject()));
    QObject::connect(treemain, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), addrselectfrm, SLOT(accept()));

    QMetaObject::connectSlotsByName(addrselectfrm);
    } // setupUi

    void retranslateUi(QDialog *addrselectfrm)
    {
    addrselectfrm->setWindowTitle(QApplication::translate("addrselectfrm", "Dialog", 0, QApplication::UnicodeUTF8));
    txtsearch->setText(QString());
    label_2->setText(QApplication::translate("addrselectfrm", "Search:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("addrselectfrm", "Directory:", 0, QApplication::UnicodeUTF8));
    btnsearch->setText(QString());
    btncancel->setText(QApplication::translate("addrselectfrm", "&Cancel", 0, QApplication::UnicodeUTF8));
    btnaccept->setText(QApplication::translate("addrselectfrm", "&Accept", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(0, QApplication::translate("addrselectfrm", "Company", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(1, QApplication::translate("addrselectfrm", "Lastname", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(2, QApplication::translate("addrselectfrm", "Firstname", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(3, QApplication::translate("addrselectfrm", "adrcompl", 0, QApplication::UnicodeUTF8));
    treemain->headerItem()->setText(4, QApplication::translate("addrselectfrm", "discount", 0, QApplication::UnicodeUTF8));
    btncancelsearch->setText(QString());
    Q_UNUSED(addrselectfrm);
    } // retranslateUi

};

namespace Ui {
    class addrselectfrm: public Ui_addrselectfrm {};
} // namespace Ui

#endif // UI_ADDRSELECTFRM_H
