/********************************************************************************
** Form generated from reading ui file 'addrfrm.ui'
**
** Created: Thu Mar 1 12:03:11 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ADDRFRM_H
#define UI_ADDRFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class Ui_addrfrm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label_5;
    QLabel *lbluser;
    QSpacerItem *spacerItem;
    QProgressBar *progbar;
    QSpacerItem *spacerItem1;
    QPushButton *btnclose;
    QTabWidget *maintab;
    QWidget *tab1;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem2;
    QLabel *label_7;
    QLabel *label_6;
    QLineEdit *adr2;
    QSpacerItem *spacerItem3;
    QSpacerItem *spacerItem4;
    QLineEdit *adr3;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *adr6;
    QLineEdit *adr4;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *adr5;
    QSpacerItem *spacerItem5;
    QLabel *label_12;
    QLineEdit *adr7;
    QLineEdit *adr8;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *adr9;
    QSpacerItem *spacerItem6;
    QLabel *adr1;
    QWidget *tab2;
    QGridLayout *gridLayout2;
    QSpacerItem *spacerItem7;
    QLabel *label_18;
    QLabel *label_17;
    QLabel *label_15;
    QLabel *label_20;
    QLabel *label_19;
    QLabel *label_16;
    QLabel *label_21;
    QLineEdit *adr11;
    QLineEdit *adr13;
    QLabel *label_24;
    QLabel *label_26;
    QLabel *label_25;
    QLineEdit *adr17;
    QLineEdit *adr18;
    QLineEdit *adr10;
    QLineEdit *adr15;
    QLineEdit *adr19;
    QLineEdit *adr16;
    QLineEdit *adr14;
    QLineEdit *adr12;
    QSpacerItem *spacerItem8;
    QSpacerItem *spacerItem9;
    QSpacerItem *spacerItem10;
    QSpacerItem *spacerItem11;
    QWidget *tab3;
    QGridLayout *gridLayout3;
    QSpacerItem *spacerItem12;
    QLineEdit *adr22;
    QSpacerItem *spacerItem13;
    QLabel *label_23;
    QSpacerItem *spacerItem14;
    QLabel *label_22;
    QTreeWidget *listrevenue;
    QFrame *line;
    QWidget *tab4;
    QGridLayout *gridLayout4;
    QPushButton *btnadrcust5;
    QPushButton *btnadrcust4;
    QPushButton *btnadrcust3;
    QPushButton *btnadrcust2;
    QPushButton *btnadrcust1;
    QLabel *lbladr24;
    QLineEdit *adr24;
    QLabel *adr30;
    QLabel *adr29;
    QLabel *label_33;
    QLabel *label_27;
    QTextEdit *adr23;
    QFrame *line_2;
    QLabel *lbladr25;
    QLabel *lbladr26;
    QLabel *lbladr27;
    QLabel *lbladr28;
    QFrame *line_3;
    QLineEdit *adr25;
    QLineEdit *adr26;
    QLineEdit *adr27;
    QLineEdit *adr28;
    QSpacerItem *spacerItem15;
    QLabel *label_34;
    QSpacerItem *spacerItem16;
    QWidget *tab5;
    QGridLayout *gridLayout5;
    QTreeWidget *listdocs;
    QWidget *tab6;
    QGridLayout *gridLayout6;
    QTreeWidget *listproc;
    QHBoxLayout *hboxLayout1;
    QGridLayout *gridLayout7;
    QPushButton *btnclear;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnsearch;
    QLineEdit *txtsearch;
    QComboBox *cmbdir;
    QSpacerItem *spacerItem17;
    QGridLayout *gridLayout8;
    QPushButton *btnnew;
    QPushButton *btndelete;
    QSpacerItem *spacerItem18;
    QPushButton *btncancel;
    QPushButton *btnsave;
    QPushButton *btnprint;
    QPushButton *btnimpexp;
    QTreeWidget *mainlistview;

    void setupUi(QWidget *addrfrm)
    {
    addrfrm->setObjectName(QString::fromUtf8("addrfrm"));
    addrfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    gridLayout = new QGridLayout(addrfrm);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label_5 = new QLabel(addrfrm);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
    label_5->setSizePolicy(sizePolicy);

    hboxLayout->addWidget(label_5);

    lbluser = new QLabel(addrfrm);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));
    QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(lbluser->sizePolicy().hasHeightForWidth());
    lbluser->setSizePolicy(sizePolicy1);

    hboxLayout->addWidget(lbluser);

    spacerItem = new QSpacerItem(361, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    progbar = new QProgressBar(addrfrm);
    progbar->setObjectName(QString::fromUtf8("progbar"));
    progbar->setMinimumSize(QSize(171, 23));
    progbar->setMaximumSize(QSize(171, 23));
    progbar->setValue(0);
    progbar->setOrientation(Qt::Horizontal);

    hboxLayout->addWidget(progbar);

    spacerItem1 = new QSpacerItem(211, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem1);

    btnclose = new QPushButton(addrfrm);
    btnclose->setObjectName(QString::fromUtf8("btnclose"));

    hboxLayout->addWidget(btnclose);


    gridLayout->addLayout(hboxLayout, 2, 0, 1, 2);

    maintab = new QTabWidget(addrfrm);
    maintab->setObjectName(QString::fromUtf8("maintab"));
    QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(maintab->sizePolicy().hasHeightForWidth());
    maintab->setSizePolicy(sizePolicy2);
    tab1 = new QWidget();
    tab1->setObjectName(QString::fromUtf8("tab1"));
    gridLayout1 = new QGridLayout(tab1);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(9);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    spacerItem2 = new QSpacerItem(172, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem2, 0, 2, 1, 1);

    label_7 = new QLabel(tab1);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    gridLayout1->addWidget(label_7, 0, 3, 1, 1);

    label_6 = new QLabel(tab1);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    gridLayout1->addWidget(label_6, 0, 0, 1, 1);

    adr2 = new QLineEdit(tab1);
    adr2->setObjectName(QString::fromUtf8("adr2"));
    adr2->setAlignment(Qt::AlignRight);

    gridLayout1->addWidget(adr2, 0, 1, 1, 1);

    spacerItem3 = new QSpacerItem(461, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    gridLayout1->addItem(spacerItem3, 1, 0, 1, 5);

    spacerItem4 = new QSpacerItem(171, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

    gridLayout1->addItem(spacerItem4, 3, 1, 1, 2);

    adr3 = new QLineEdit(tab1);
    adr3->setObjectName(QString::fromUtf8("adr3"));
    QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(0));
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(adr3->sizePolicy().hasHeightForWidth());
    adr3->setSizePolicy(sizePolicy3);

    gridLayout1->addWidget(adr3, 2, 1, 1, 4);

    label_8 = new QLabel(tab1);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    gridLayout1->addWidget(label_8, 2, 0, 1, 1);

    label_9 = new QLabel(tab1);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    gridLayout1->addWidget(label_9, 4, 0, 1, 1);

    adr6 = new QLineEdit(tab1);
    adr6->setObjectName(QString::fromUtf8("adr6"));

    gridLayout1->addWidget(adr6, 4, 1, 1, 4);

    adr4 = new QLineEdit(tab1);
    adr4->setObjectName(QString::fromUtf8("adr4"));

    gridLayout1->addWidget(adr4, 5, 1, 1, 4);

    label_10 = new QLabel(tab1);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    gridLayout1->addWidget(label_10, 5, 0, 1, 1);

    label_11 = new QLabel(tab1);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    gridLayout1->addWidget(label_11, 6, 0, 1, 1);

    adr5 = new QLineEdit(tab1);
    adr5->setObjectName(QString::fromUtf8("adr5"));

    gridLayout1->addWidget(adr5, 6, 1, 1, 4);

    spacerItem5 = new QSpacerItem(161, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

    gridLayout1->addItem(spacerItem5, 7, 1, 1, 2);

    label_12 = new QLabel(tab1);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    gridLayout1->addWidget(label_12, 8, 0, 1, 1);

    adr7 = new QLineEdit(tab1);
    adr7->setObjectName(QString::fromUtf8("adr7"));

    gridLayout1->addWidget(adr7, 8, 1, 1, 4);

    adr8 = new QLineEdit(tab1);
    adr8->setObjectName(QString::fromUtf8("adr8"));

    gridLayout1->addWidget(adr8, 9, 1, 1, 4);

    label_13 = new QLabel(tab1);
    label_13->setObjectName(QString::fromUtf8("label_13"));

    gridLayout1->addWidget(label_13, 9, 0, 1, 1);

    label_14 = new QLabel(tab1);
    label_14->setObjectName(QString::fromUtf8("label_14"));

    gridLayout1->addWidget(label_14, 10, 0, 1, 1);

    adr9 = new QLineEdit(tab1);
    adr9->setObjectName(QString::fromUtf8("adr9"));

    gridLayout1->addWidget(adr9, 10, 1, 1, 4);

    spacerItem6 = new QSpacerItem(20, 211, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout1->addItem(spacerItem6, 11, 1, 1, 1);

    adr1 = new QLabel(tab1);
    adr1->setObjectName(QString::fromUtf8("adr1"));
    QSizePolicy sizePolicy4(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(adr1->sizePolicy().hasHeightForWidth());
    adr1->setSizePolicy(sizePolicy4);

    gridLayout1->addWidget(adr1, 0, 4, 1, 1);

    maintab->addTab(tab1, QApplication::translate("addrfrm", "Address", 0, QApplication::UnicodeUTF8));
    tab2 = new QWidget();
    tab2->setObjectName(QString::fromUtf8("tab2"));
    gridLayout2 = new QGridLayout(tab2);
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(9);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    spacerItem7 = new QSpacerItem(20, 141, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout2->addItem(spacerItem7, 13, 1, 1, 1);

    label_18 = new QLabel(tab2);
    label_18->setObjectName(QString::fromUtf8("label_18"));

    gridLayout2->addWidget(label_18, 4, 0, 1, 1);

    label_17 = new QLabel(tab2);
    label_17->setObjectName(QString::fromUtf8("label_17"));

    gridLayout2->addWidget(label_17, 2, 0, 1, 1);

    label_15 = new QLabel(tab2);
    label_15->setObjectName(QString::fromUtf8("label_15"));

    gridLayout2->addWidget(label_15, 0, 0, 1, 1);

    label_20 = new QLabel(tab2);
    label_20->setObjectName(QString::fromUtf8("label_20"));

    gridLayout2->addWidget(label_20, 6, 0, 1, 1);

    label_19 = new QLabel(tab2);
    label_19->setObjectName(QString::fromUtf8("label_19"));

    gridLayout2->addWidget(label_19, 5, 0, 1, 1);

    label_16 = new QLabel(tab2);
    label_16->setObjectName(QString::fromUtf8("label_16"));

    gridLayout2->addWidget(label_16, 1, 0, 1, 1);

    label_21 = new QLabel(tab2);
    label_21->setObjectName(QString::fromUtf8("label_21"));

    gridLayout2->addWidget(label_21, 8, 0, 1, 1);

    adr11 = new QLineEdit(tab2);
    adr11->setObjectName(QString::fromUtf8("adr11"));
    adr11->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr11, 1, 1, 1, 1);

    adr13 = new QLineEdit(tab2);
    adr13->setObjectName(QString::fromUtf8("adr13"));
    adr13->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr13, 4, 1, 1, 1);

    label_24 = new QLabel(tab2);
    label_24->setObjectName(QString::fromUtf8("label_24"));

    gridLayout2->addWidget(label_24, 9, 0, 1, 1);

    label_26 = new QLabel(tab2);
    label_26->setObjectName(QString::fromUtf8("label_26"));

    gridLayout2->addWidget(label_26, 12, 0, 1, 1);

    label_25 = new QLabel(tab2);
    label_25->setObjectName(QString::fromUtf8("label_25"));

    gridLayout2->addWidget(label_25, 10, 0, 1, 1);

    adr17 = new QLineEdit(tab2);
    adr17->setObjectName(QString::fromUtf8("adr17"));
    adr17->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr17, 9, 1, 1, 2);

    adr18 = new QLineEdit(tab2);
    adr18->setObjectName(QString::fromUtf8("adr18"));
    adr18->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr18, 10, 1, 1, 2);

    adr10 = new QLineEdit(tab2);
    adr10->setObjectName(QString::fromUtf8("adr10"));
    adr10->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr10, 0, 1, 1, 1);

    adr15 = new QLineEdit(tab2);
    adr15->setObjectName(QString::fromUtf8("adr15"));
    adr15->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr15, 6, 1, 1, 1);

    adr19 = new QLineEdit(tab2);
    adr19->setObjectName(QString::fromUtf8("adr19"));
    adr19->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr19, 12, 1, 1, 2);

    adr16 = new QLineEdit(tab2);
    adr16->setObjectName(QString::fromUtf8("adr16"));
    adr16->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr16, 8, 1, 1, 2);

    adr14 = new QLineEdit(tab2);
    adr14->setObjectName(QString::fromUtf8("adr14"));
    adr14->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr14, 5, 1, 1, 1);

    adr12 = new QLineEdit(tab2);
    adr12->setObjectName(QString::fromUtf8("adr12"));
    adr12->setAlignment(Qt::AlignLeading);

    gridLayout2->addWidget(adr12, 2, 1, 1, 1);

    spacerItem8 = new QSpacerItem(161, 201, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout2->addItem(spacerItem8, 0, 2, 8, 1);

    spacerItem9 = new QSpacerItem(291, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    gridLayout2->addItem(spacerItem9, 3, 0, 1, 2);

    spacerItem10 = new QSpacerItem(291, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    gridLayout2->addItem(spacerItem10, 7, 0, 1, 2);

    spacerItem11 = new QSpacerItem(461, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    gridLayout2->addItem(spacerItem11, 11, 0, 1, 3);

    maintab->addTab(tab2, QApplication::translate("addrfrm", "Communication", 0, QApplication::UnicodeUTF8));
    tab3 = new QWidget();
    tab3->setObjectName(QString::fromUtf8("tab3"));
    gridLayout3 = new QGridLayout(tab3);
    gridLayout3->setSpacing(6);
    gridLayout3->setMargin(9);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    spacerItem12 = new QSpacerItem(461, 301, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout3->addItem(spacerItem12, 4, 0, 1, 3);

    adr22 = new QLineEdit(tab3);
    adr22->setObjectName(QString::fromUtf8("adr22"));
    QSizePolicy sizePolicy5(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(adr22->sizePolicy().hasHeightForWidth());
    adr22->setSizePolicy(sizePolicy5);
    adr22->setMaximumSize(QSize(61, 25));
    adr22->setAlignment(Qt::AlignRight);

    gridLayout3->addWidget(adr22, 3, 1, 1, 1);

    spacerItem13 = new QSpacerItem(241, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout3->addItem(spacerItem13, 3, 2, 1, 1);

    label_23 = new QLabel(tab3);
    label_23->setObjectName(QString::fromUtf8("label_23"));

    gridLayout3->addWidget(label_23, 3, 0, 1, 1);

    spacerItem14 = new QSpacerItem(20, 151, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout3->addItem(spacerItem14, 1, 0, 1, 1);

    label_22 = new QLabel(tab3);
    label_22->setObjectName(QString::fromUtf8("label_22"));

    gridLayout3->addWidget(label_22, 0, 0, 1, 1);

    listrevenue = new QTreeWidget(tab3);
    listrevenue->setObjectName(QString::fromUtf8("listrevenue"));

    gridLayout3->addWidget(listrevenue, 0, 1, 2, 2);

    line = new QFrame(tab3);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout3->addWidget(line, 2, 0, 1, 3);

    maintab->addTab(tab3, QApplication::translate("addrfrm", "Customer", 0, QApplication::UnicodeUTF8));
    tab4 = new QWidget();
    tab4->setObjectName(QString::fromUtf8("tab4"));
    gridLayout4 = new QGridLayout(tab4);
    gridLayout4->setSpacing(6);
    gridLayout4->setMargin(9);
    gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
    btnadrcust5 = new QPushButton(tab4);
    btnadrcust5->setObjectName(QString::fromUtf8("btnadrcust5"));
    QSizePolicy sizePolicy6(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(btnadrcust5->sizePolicy().hasHeightForWidth());
    btnadrcust5->setSizePolicy(sizePolicy6);
    btnadrcust5->setIcon(QIcon(QString::fromUtf8(":/images/images/xclipboard.png")));

    gridLayout4->addWidget(btnadrcust5, 7, 0, 1, 1);

    btnadrcust4 = new QPushButton(tab4);
    btnadrcust4->setObjectName(QString::fromUtf8("btnadrcust4"));
    QSizePolicy sizePolicy7(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy7.setHorizontalStretch(0);
    sizePolicy7.setVerticalStretch(0);
    sizePolicy7.setHeightForWidth(btnadrcust4->sizePolicy().hasHeightForWidth());
    btnadrcust4->setSizePolicy(sizePolicy7);
    btnadrcust4->setIcon(QIcon(QString::fromUtf8(":/images/images/xclipboard.png")));

    gridLayout4->addWidget(btnadrcust4, 6, 0, 1, 1);

    btnadrcust3 = new QPushButton(tab4);
    btnadrcust3->setObjectName(QString::fromUtf8("btnadrcust3"));
    QSizePolicy sizePolicy8(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy8.setHorizontalStretch(0);
    sizePolicy8.setVerticalStretch(0);
    sizePolicy8.setHeightForWidth(btnadrcust3->sizePolicy().hasHeightForWidth());
    btnadrcust3->setSizePolicy(sizePolicy8);
    btnadrcust3->setIcon(QIcon(QString::fromUtf8(":/images/images/xclipboard.png")));

    gridLayout4->addWidget(btnadrcust3, 5, 0, 1, 1);

    btnadrcust2 = new QPushButton(tab4);
    btnadrcust2->setObjectName(QString::fromUtf8("btnadrcust2"));
    QSizePolicy sizePolicy9(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy9.setHorizontalStretch(0);
    sizePolicy9.setVerticalStretch(0);
    sizePolicy9.setHeightForWidth(btnadrcust2->sizePolicy().hasHeightForWidth());
    btnadrcust2->setSizePolicy(sizePolicy9);
    btnadrcust2->setIcon(QIcon(QString::fromUtf8(":/images/images/xclipboard.png")));

    gridLayout4->addWidget(btnadrcust2, 4, 0, 1, 1);

    btnadrcust1 = new QPushButton(tab4);
    btnadrcust1->setObjectName(QString::fromUtf8("btnadrcust1"));
    QSizePolicy sizePolicy10(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy10.setHorizontalStretch(0);
    sizePolicy10.setVerticalStretch(0);
    sizePolicy10.setHeightForWidth(btnadrcust1->sizePolicy().hasHeightForWidth());
    btnadrcust1->setSizePolicy(sizePolicy10);
    btnadrcust1->setIcon(QIcon(QString::fromUtf8(":/images/images/xclipboard.png")));

    gridLayout4->addWidget(btnadrcust1, 3, 0, 1, 1);

    lbladr24 = new QLabel(tab4);
    lbladr24->setObjectName(QString::fromUtf8("lbladr24"));

    gridLayout4->addWidget(lbladr24, 3, 1, 1, 2);

    adr24 = new QLineEdit(tab4);
    adr24->setObjectName(QString::fromUtf8("adr24"));
    adr24->setAlignment(Qt::AlignRight);

    gridLayout4->addWidget(adr24, 3, 3, 1, 3);

    adr30 = new QLabel(tab4);
    adr30->setObjectName(QString::fromUtf8("adr30"));
    QSizePolicy sizePolicy11(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy11.setHorizontalStretch(0);
    sizePolicy11.setVerticalStretch(0);
    sizePolicy11.setHeightForWidth(adr30->sizePolicy().hasHeightForWidth());
    adr30->setSizePolicy(sizePolicy11);
    adr30->setMinimumSize(QSize(91, 20));

    gridLayout4->addWidget(adr30, 10, 5, 1, 1);

    adr29 = new QLabel(tab4);
    adr29->setObjectName(QString::fromUtf8("adr29"));
    QSizePolicy sizePolicy12(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy12.setHorizontalStretch(0);
    sizePolicy12.setVerticalStretch(0);
    sizePolicy12.setHeightForWidth(adr29->sizePolicy().hasHeightForWidth());
    adr29->setSizePolicy(sizePolicy12);
    adr29->setMinimumSize(QSize(91, 20));

    gridLayout4->addWidget(adr29, 10, 2, 1, 2);

    label_33 = new QLabel(tab4);
    label_33->setObjectName(QString::fromUtf8("label_33"));

    gridLayout4->addWidget(label_33, 10, 0, 1, 2);

    label_27 = new QLabel(tab4);
    label_27->setObjectName(QString::fromUtf8("label_27"));

    gridLayout4->addWidget(label_27, 0, 0, 1, 2);

    adr23 = new QTextEdit(tab4);
    adr23->setObjectName(QString::fromUtf8("adr23"));

    gridLayout4->addWidget(adr23, 1, 0, 1, 6);

    line_2 = new QFrame(tab4);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);

    gridLayout4->addWidget(line_2, 2, 0, 1, 6);

    lbladr25 = new QLabel(tab4);
    lbladr25->setObjectName(QString::fromUtf8("lbladr25"));

    gridLayout4->addWidget(lbladr25, 4, 1, 1, 2);

    lbladr26 = new QLabel(tab4);
    lbladr26->setObjectName(QString::fromUtf8("lbladr26"));

    gridLayout4->addWidget(lbladr26, 5, 1, 1, 2);

    lbladr27 = new QLabel(tab4);
    lbladr27->setObjectName(QString::fromUtf8("lbladr27"));

    gridLayout4->addWidget(lbladr27, 6, 1, 1, 2);

    lbladr28 = new QLabel(tab4);
    lbladr28->setObjectName(QString::fromUtf8("lbladr28"));

    gridLayout4->addWidget(lbladr28, 7, 1, 1, 2);

    line_3 = new QFrame(tab4);
    line_3->setObjectName(QString::fromUtf8("line_3"));
    line_3->setFrameShape(QFrame::HLine);
    line_3->setFrameShadow(QFrame::Sunken);

    gridLayout4->addWidget(line_3, 8, 0, 2, 6);

    adr25 = new QLineEdit(tab4);
    adr25->setObjectName(QString::fromUtf8("adr25"));
    adr25->setAlignment(Qt::AlignRight);

    gridLayout4->addWidget(adr25, 4, 3, 1, 3);

    adr26 = new QLineEdit(tab4);
    adr26->setObjectName(QString::fromUtf8("adr26"));
    adr26->setAlignment(Qt::AlignRight);

    gridLayout4->addWidget(adr26, 5, 3, 1, 3);

    adr27 = new QLineEdit(tab4);
    adr27->setObjectName(QString::fromUtf8("adr27"));
    adr27->setAlignment(Qt::AlignRight);

    gridLayout4->addWidget(adr27, 6, 3, 1, 3);

    adr28 = new QLineEdit(tab4);
    adr28->setObjectName(QString::fromUtf8("adr28"));
    adr28->setAlignment(Qt::AlignRight);

    gridLayout4->addWidget(adr28, 7, 3, 1, 3);

    spacerItem15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout4->addItem(spacerItem15, 0, 3, 1, 3);

    label_34 = new QLabel(tab4);
    label_34->setObjectName(QString::fromUtf8("label_34"));

    gridLayout4->addWidget(label_34, 9, 4, 2, 1);

    spacerItem16 = new QSpacerItem(451, 101, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout4->addItem(spacerItem16, 11, 0, 1, 6);

    maintab->addTab(tab4, QApplication::translate("addrfrm", "Ulterior Data", 0, QApplication::UnicodeUTF8));
    tab5 = new QWidget();
    tab5->setObjectName(QString::fromUtf8("tab5"));
    gridLayout5 = new QGridLayout(tab5);
    gridLayout5->setSpacing(6);
    gridLayout5->setMargin(9);
    gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
    listdocs = new QTreeWidget(tab5);
    listdocs->setObjectName(QString::fromUtf8("listdocs"));
    listdocs->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout5->addWidget(listdocs, 0, 0, 1, 1);

    maintab->addTab(tab5, QApplication::translate("addrfrm", "Documents", 0, QApplication::UnicodeUTF8));
    tab6 = new QWidget();
    tab6->setObjectName(QString::fromUtf8("tab6"));
    gridLayout6 = new QGridLayout(tab6);
    gridLayout6->setSpacing(6);
    gridLayout6->setMargin(9);
    gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
    listproc = new QTreeWidget(tab6);
    listproc->setObjectName(QString::fromUtf8("listproc"));

    gridLayout6->addWidget(listproc, 0, 0, 1, 1);

    maintab->addTab(tab6, QApplication::translate("addrfrm", "Procedures", 0, QApplication::UnicodeUTF8));

    gridLayout->addWidget(maintab, 1, 1, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    gridLayout7 = new QGridLayout();
    gridLayout7->setSpacing(6);
    gridLayout7->setMargin(0);
    gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
    btnclear = new QPushButton(addrfrm);
    btnclear->setObjectName(QString::fromUtf8("btnclear"));
    btnclear->setIcon(QIcon(QString::fromUtf8(":/images/images/kill.png")));

    gridLayout7->addWidget(btnclear, 1, 3, 1, 1);

    label = new QLabel(addrfrm);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout7->addWidget(label, 0, 0, 1, 1);

    label_2 = new QLabel(addrfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout7->addWidget(label_2, 1, 0, 1, 1);

    btnsearch = new QPushButton(addrfrm);
    btnsearch->setObjectName(QString::fromUtf8("btnsearch"));
    btnsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));

    gridLayout7->addWidget(btnsearch, 1, 2, 1, 1);

    txtsearch = new QLineEdit(addrfrm);
    txtsearch->setObjectName(QString::fromUtf8("txtsearch"));

    gridLayout7->addWidget(txtsearch, 1, 1, 1, 1);

    cmbdir = new QComboBox(addrfrm);
    cmbdir->setObjectName(QString::fromUtf8("cmbdir"));

    gridLayout7->addWidget(cmbdir, 0, 1, 1, 3);


    hboxLayout1->addLayout(gridLayout7);

    spacerItem17 = new QSpacerItem(251, 51, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem17);

    gridLayout8 = new QGridLayout();
    gridLayout8->setSpacing(6);
    gridLayout8->setMargin(0);
    gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
    btnnew = new QPushButton(addrfrm);
    btnnew->setObjectName(QString::fromUtf8("btnnew"));
    btnnew->setMinimumSize(QSize(41, 41));
    btnnew->setMaximumSize(QSize(41, 41));
    btnnew->setIcon(QIcon(QString::fromUtf8(":/images/images/filenew.png")));
    btnnew->setIconSize(QSize(32, 32));

    gridLayout8->addWidget(btnnew, 0, 0, 1, 1);

    btndelete = new QPushButton(addrfrm);
    btndelete->setObjectName(QString::fromUtf8("btndelete"));
    btndelete->setMinimumSize(QSize(41, 41));
    btndelete->setMaximumSize(QSize(41, 41));
    btndelete->setIcon(QIcon(QString::fromUtf8(":/images/images/editdelete.png")));
    btndelete->setIconSize(QSize(32, 32));

    gridLayout8->addWidget(btndelete, 0, 3, 1, 1);

    spacerItem18 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    gridLayout8->addItem(spacerItem18, 0, 5, 1, 1);

    btncancel = new QPushButton(addrfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setMinimumSize(QSize(41, 41));
    btncancel->setMaximumSize(QSize(41, 41));
    btncancel->setIcon(QIcon(QString::fromUtf8(":/images/images/undo.png")));
    btncancel->setIconSize(QSize(32, 32));

    gridLayout8->addWidget(btncancel, 0, 2, 1, 1);

    btnsave = new QPushButton(addrfrm);
    btnsave->setObjectName(QString::fromUtf8("btnsave"));
    btnsave->setMinimumSize(QSize(41, 41));
    btnsave->setMaximumSize(QSize(41, 41));
    btnsave->setIcon(QIcon(QString::fromUtf8(":/images/images/filesave.png")));
    btnsave->setIconSize(QSize(32, 32));

    gridLayout8->addWidget(btnsave, 0, 1, 1, 1);

    btnprint = new QPushButton(addrfrm);
    btnprint->setObjectName(QString::fromUtf8("btnprint"));
    btnprint->setMinimumSize(QSize(41, 41));
    btnprint->setMaximumSize(QSize(41, 41));
    btnprint->setIcon(QIcon(QString::fromUtf8(":/images/images/fileprint.png")));
    btnprint->setIconSize(QSize(32, 32));

    gridLayout8->addWidget(btnprint, 0, 4, 1, 1);

    btnimpexp = new QPushButton(addrfrm);
    btnimpexp->setObjectName(QString::fromUtf8("btnimpexp"));
    btnimpexp->setMinimumSize(QSize(41, 41));
    btnimpexp->setMaximumSize(QSize(41, 41));
    btnimpexp->setIcon(QIcon(QString::fromUtf8(":/images/images/impexp.png")));
    btnimpexp->setIconSize(QSize(32, 32));

    gridLayout8->addWidget(btnimpexp, 0, 6, 1, 1);


    hboxLayout1->addLayout(gridLayout8);


    gridLayout->addLayout(hboxLayout1, 0, 0, 1, 2);

    mainlistview = new QTreeWidget(addrfrm);
    mainlistview->setObjectName(QString::fromUtf8("mainlistview"));
    QSizePolicy sizePolicy13(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(7));
    sizePolicy13.setHorizontalStretch(0);
    sizePolicy13.setVerticalStretch(0);
    sizePolicy13.setHeightForWidth(mainlistview->sizePolicy().hasHeightForWidth());
    mainlistview->setSizePolicy(sizePolicy13);
    mainlistview->setMinimumSize(QSize(411, 0));
    mainlistview->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout->addWidget(mainlistview, 1, 0, 1, 1);


    retranslateUi(addrfrm);

    QSize size(918, 699);
    size = size.expandedTo(addrfrm->minimumSizeHint());
    addrfrm->resize(size);

    QObject::connect(btnclose, SIGNAL(released()), addrfrm, SLOT(close()));

    maintab->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(addrfrm);
    } // setupUi

    void retranslateUi(QWidget *addrfrm)
    {
    addrfrm->setWindowTitle(QApplication::translate("addrfrm", "Directories...", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("addrfrm", "User:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    btnclose->setText(QApplication::translate("addrfrm", "&Close", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("addrfrm", "ID:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("addrfrm", "Address-ID:", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("addrfrm", "Company:", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("addrfrm", "Mr. / Ms.:", 0, QApplication::UnicodeUTF8));
    adr6->setText(QString());
    label_10->setText(QApplication::translate("addrfrm", "Firstname:", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("addrfrm", "Lastname:", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("addrfrm", "PO-Box:", 0, QApplication::UnicodeUTF8));
    adr8->setText(QString());
    label_13->setText(QApplication::translate("addrfrm", "Street & Nr.:", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("addrfrm", "ZIP, Location:", 0, QApplication::UnicodeUTF8));
    adr1->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab1), QApplication::translate("addrfrm", "Address", 0, QApplication::UnicodeUTF8));
    label_18->setText(QApplication::translate("addrfrm", "Telefon P:", 0, QApplication::UnicodeUTF8));
    label_17->setText(QApplication::translate("addrfrm", "Fax B:", 0, QApplication::UnicodeUTF8));
    label_15->setText(QApplication::translate("addrfrm", "Telefon B:", 0, QApplication::UnicodeUTF8));
    label_20->setText(QApplication::translate("addrfrm", "Mobile:", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("addrfrm", "Fax P:", 0, QApplication::UnicodeUTF8));
    label_16->setText(QApplication::translate("addrfrm", "Telefon dir. B:", 0, QApplication::UnicodeUTF8));
    label_21->setText(QApplication::translate("addrfrm", "E-Mail 1:", 0, QApplication::UnicodeUTF8));
    label_24->setText(QApplication::translate("addrfrm", "E-Mail 2:", 0, QApplication::UnicodeUTF8));
    label_26->setText(QApplication::translate("addrfrm", "Website:", 0, QApplication::UnicodeUTF8));
    label_25->setText(QApplication::translate("addrfrm", "E-Mail 3:", 0, QApplication::UnicodeUTF8));
    adr10->setText(QString());
    maintab->setTabText(maintab->indexOf(tab2), QApplication::translate("addrfrm", "Communication", 0, QApplication::UnicodeUTF8));
    label_23->setText(QApplication::translate("addrfrm", "Discount %:", 0, QApplication::UnicodeUTF8));
    label_22->setText(QApplication::translate("addrfrm", "Revenue in CHF:", 0, QApplication::UnicodeUTF8));
    listrevenue->headerItem()->setText(0, QApplication::translate("addrfrm", "Year", 0, QApplication::UnicodeUTF8));
    listrevenue->headerItem()->setText(1, QApplication::translate("addrfrm", "Revenue", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab3), QApplication::translate("addrfrm", "Customer", 0, QApplication::UnicodeUTF8));
    lbladr24->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    adr30->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    adr29->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    label_33->setText(QApplication::translate("addrfrm", "Created:", 0, QApplication::UnicodeUTF8));
    label_27->setText(QApplication::translate("addrfrm", "Comments:", 0, QApplication::UnicodeUTF8));
    lbladr25->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    lbladr26->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    lbladr27->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    lbladr28->setText(QApplication::translate("addrfrm", "-", 0, QApplication::UnicodeUTF8));
    label_34->setText(QApplication::translate("addrfrm", "Modified:", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab4), QApplication::translate("addrfrm", "Ulterior Data", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab5), QApplication::translate("addrfrm", "Documents", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab6), QApplication::translate("addrfrm", "Procedures", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("addrfrm", "Directory:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("addrfrm", "Search:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(addrfrm);
    } // retranslateUi

};

namespace Ui {
    class addrfrm: public Ui_addrfrm {};
} // namespace Ui

#endif // UI_ADDRFRM_H
