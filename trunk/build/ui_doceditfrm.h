/********************************************************************************
** Form generated from reading ui file 'doceditfrm.ui'
**
** Created: Thu Apr 5 22:13:14 2007
**      by: Qt User Interface Compiler version 4.3.0beta
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DOCEDITFRM_H
#define UI_DOCEDITFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_doceditfrm
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QPushButton *btnclose;
    QLabel *label_5;
    QLabel *lbluser;
    QGroupBox *groupBox;
    QFrame *line_2;
    QFrame *line;
    QLabel *label_13;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout2;
    QPushButton *btncalc;
    QFrame *line_5;
    QLineEdit *boxtot_incl;
    QLabel *label_12;
    QPushButton *btnvat;
    QLineEdit *boxvat;
    QLineEdit *boxtot_excl;
    QLabel *label_11;
    QLabel *label_19;
    QLabel *label_10;
    QLineEdit *boxdiscount;
    QLabel *label_9;
    QLineEdit *boxtot;
    QTabWidget *mainwidget;
    QWidget *tab1;
    QGridLayout *gridLayout2;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *txtsalutation;
    QTextEdit *boxotherinfo;
    QWidget *tab2;
    QGridLayout *gridLayout3;
    QTableWidget *tabmain;
    QWidget *tab3;
    QGridLayout *gridLayout4;
    QTextEdit *boxcomments;
    QGroupBox *groupBox_2;
    QWidget *widget;
    QGridLayout *gridLayout5;
    QGridLayout *gridLayout6;
    QComboBox *cmbdoc;
    QHBoxLayout *hboxLayout3;
    QPushButton *btnclearsearch;
    QLabel *label_4;
    QLabel *lblID;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *txtdoccount;
    QPushButton *btnsearchaddr;
    QTextEdit *boxaddress;
    QLabel *label;
    QGridLayout *gridLayout7;
    QGridLayout *gridLayout8;
    QDateEdit *boxdate;
    QLabel *label_3;
    QHBoxLayout *hboxLayout4;
    QPushButton *btnnew;
    QPushButton *btnopen;
    QPushButton *btnsave;
    QPushButton *btnprint;
    QPushButton *btncomplete;

    void setupUi(QWidget *doceditfrm)
    {
    if (doceditfrm->objectName().isEmpty())
        doceditfrm->setObjectName(QString::fromUtf8("doceditfrm"));
    QSize size(779, 718);
    size = size.expandedTo(doceditfrm->minimumSizeHint());
    doceditfrm->resize(size);
    doceditfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/wordprocessing.png")));
    gridLayout = new QGridLayout(doceditfrm);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout->setMargin(9);
#endif
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    groupBox_3 = new QGroupBox(doceditfrm);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    groupBox_3->setMinimumSize(QSize(761, 191));
    groupBox_3->setMaximumSize(QSize(16777215, 191));
    gridLayout1 = new QGridLayout(groupBox_3);
#ifndef Q_OS_MAC
    gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout1->setMargin(9);
#endif
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout->setMargin(0);
#endif
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout = new QVBoxLayout();
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout->setMargin(0);
#endif
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));

    vboxLayout->addItem(new QSpacerItem(20, 131, QSizePolicy::Minimum, QSizePolicy::Fixed));

    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout1->setMargin(0);
#endif
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    btnclose = new QPushButton(groupBox_3);
    btnclose->setObjectName(QString::fromUtf8("btnclose"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(btnclose->sizePolicy().hasHeightForWidth());
    btnclose->setSizePolicy(sizePolicy);

    hboxLayout1->addWidget(btnclose);

    label_5 = new QLabel(groupBox_3);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
    label_5->setSizePolicy(sizePolicy);

    hboxLayout1->addWidget(label_5);

    lbluser = new QLabel(groupBox_3);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));

    hboxLayout1->addWidget(lbluser);


    vboxLayout->addLayout(hboxLayout1);


    hboxLayout->addLayout(vboxLayout);

    groupBox = new QGroupBox(groupBox_3);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy);
    groupBox->setMinimumSize(QSize(281, 171));
    groupBox->setMaximumSize(QSize(281, 171));
    line_2 = new QFrame(groupBox);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setGeometry(QRect(10, 132, 265, 2));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);
    line = new QFrame(groupBox);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(10, 100, 265, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    label_13 = new QLabel(groupBox);
    label_13->setObjectName(QString::fromUtf8("label_13"));
    label_13->setGeometry(QRect(20, 110, 121, 17));
    layoutWidget = new QWidget(groupBox);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(9, 140, 261, 29));
    hboxLayout2 = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
    hboxLayout2->setSpacing(6);
#endif
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));

    hboxLayout2->addItem(new QSpacerItem(161, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    btncalc = new QPushButton(layoutWidget);
    btncalc->setObjectName(QString::fromUtf8("btncalc"));

    hboxLayout2->addWidget(btncalc);

    line_5 = new QFrame(groupBox);
    line_5->setObjectName(QString::fromUtf8("line_5"));
    line_5->setGeometry(QRect(10, 130, 265, 2));
    line_5->setFrameShape(QFrame::HLine);
    line_5->setFrameShadow(QFrame::Sunken);
    boxtot_incl = new QLineEdit(groupBox);
    boxtot_incl->setObjectName(QString::fromUtf8("boxtot_incl"));
    boxtot_incl->setGeometry(QRect(160, 107, 113, 21));
    boxtot_incl->setMinimumSize(QSize(113, 21));
    boxtot_incl->setMaximumSize(QSize(113, 21));
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    boxtot_incl->setFont(font);
    label_12 = new QLabel(groupBox);
    label_12->setObjectName(QString::fromUtf8("label_12"));
    label_12->setGeometry(QRect(20, 80, 101, 17));
    label_12->setMinimumSize(QSize(101, 17));
    label_12->setMaximumSize(QSize(101, 17));
    btnvat = new QPushButton(groupBox);
    btnvat->setObjectName(QString::fromUtf8("btnvat"));
    btnvat->setGeometry(QRect(130, 78, 21, 20));
    btnvat->setMinimumSize(QSize(21, 20));
    btnvat->setMaximumSize(QSize(21, 20));
    btnvat->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
    boxvat = new QLineEdit(groupBox);
    boxvat->setObjectName(QString::fromUtf8("boxvat"));
    boxvat->setGeometry(QRect(160, 77, 113, 21));
    sizePolicy.setHeightForWidth(boxvat->sizePolicy().hasHeightForWidth());
    boxvat->setSizePolicy(sizePolicy);
    boxvat->setMinimumSize(QSize(113, 21));
    boxvat->setMaximumSize(QSize(113, 21));
    boxtot_excl = new QLineEdit(groupBox);
    boxtot_excl->setObjectName(QString::fromUtf8("boxtot_excl"));
    boxtot_excl->setGeometry(QRect(160, 54, 113, 21));
    sizePolicy.setHeightForWidth(boxtot_excl->sizePolicy().hasHeightForWidth());
    boxtot_excl->setSizePolicy(sizePolicy);
    boxtot_excl->setMinimumSize(QSize(113, 21));
    boxtot_excl->setMaximumSize(QSize(113, 21));
    label_11 = new QLabel(groupBox);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    label_11->setGeometry(QRect(20, 56, 121, 21));
    label_11->setMinimumSize(QSize(121, 21));
    label_11->setMaximumSize(QSize(121, 21));
    label_19 = new QLabel(groupBox);
    label_19->setObjectName(QString::fromUtf8("label_19"));
    label_19->setGeometry(QRect(250, 34, 21, 17));
    sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
    label_19->setSizePolicy(sizePolicy);
    label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    label_10 = new QLabel(groupBox);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(70, 30, 81, 21));
    label_10->setMinimumSize(QSize(81, 21));
    label_10->setMaximumSize(QSize(81, 21));
    label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    boxdiscount = new QLineEdit(groupBox);
    boxdiscount->setObjectName(QString::fromUtf8("boxdiscount"));
    boxdiscount->setGeometry(QRect(160, 32, 80, 21));
    sizePolicy.setHeightForWidth(boxdiscount->sizePolicy().hasHeightForWidth());
    boxdiscount->setSizePolicy(sizePolicy);
    boxdiscount->setMinimumSize(QSize(80, 21));
    boxdiscount->setMaximumSize(QSize(80, 21));
    boxdiscount->setAlignment(Qt::AlignRight);
    label_9 = new QLabel(groupBox);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(20, 10, 121, 17));
    boxtot = new QLineEdit(groupBox);
    boxtot->setObjectName(QString::fromUtf8("boxtot"));
    boxtot->setGeometry(QRect(160, 10, 113, 21));
    sizePolicy.setHeightForWidth(boxtot->sizePolicy().hasHeightForWidth());
    boxtot->setSizePolicy(sizePolicy);
    boxtot->setMinimumSize(QSize(113, 21));
    boxtot->setMaximumSize(QSize(113, 21));

    hboxLayout->addWidget(groupBox);


    gridLayout1->addLayout(hboxLayout, 0, 0, 1, 1);


    gridLayout->addWidget(groupBox_3, 2, 0, 1, 1);

    mainwidget = new QTabWidget(doceditfrm);
    mainwidget->setObjectName(QString::fromUtf8("mainwidget"));
    mainwidget->setMinimumSize(QSize(0, 301));
    tab1 = new QWidget();
    tab1->setObjectName(QString::fromUtf8("tab1"));
    gridLayout2 = new QGridLayout(tab1);
#ifndef Q_OS_MAC
    gridLayout2->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout2->setMargin(9);
#endif
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    label_20 = new QLabel(tab1);
    label_20->setObjectName(QString::fromUtf8("label_20"));

    gridLayout2->addWidget(label_20, 0, 0, 1, 1);

    label_21 = new QLabel(tab1);
    label_21->setObjectName(QString::fromUtf8("label_21"));

    gridLayout2->addWidget(label_21, 1, 0, 1, 2);

    txtsalutation = new QLineEdit(tab1);
    txtsalutation->setObjectName(QString::fromUtf8("txtsalutation"));

    gridLayout2->addWidget(txtsalutation, 0, 1, 1, 1);

    boxotherinfo = new QTextEdit(tab1);
    boxotherinfo->setObjectName(QString::fromUtf8("boxotherinfo"));

    gridLayout2->addWidget(boxotherinfo, 2, 0, 1, 2);

    mainwidget->addTab(tab1, QString());
    tab2 = new QWidget();
    tab2->setObjectName(QString::fromUtf8("tab2"));
    gridLayout3 = new QGridLayout(tab2);
#ifndef Q_OS_MAC
    gridLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout3->setMargin(9);
#endif
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    tabmain = new QTableWidget(tab2);
    tabmain->setObjectName(QString::fromUtf8("tabmain"));
    QFont font1;
    font1.setPointSize(8);
    tabmain->setFont(font1);
    tabmain->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout3->addWidget(tabmain, 0, 0, 1, 1);

    mainwidget->addTab(tab2, QString());
    tab3 = new QWidget();
    tab3->setObjectName(QString::fromUtf8("tab3"));
    gridLayout4 = new QGridLayout(tab3);
#ifndef Q_OS_MAC
    gridLayout4->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout4->setMargin(9);
#endif
    gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
    boxcomments = new QTextEdit(tab3);
    boxcomments->setObjectName(QString::fromUtf8("boxcomments"));

    gridLayout4->addWidget(boxcomments, 0, 0, 1, 1);

    mainwidget->addTab(tab3, QString());

    gridLayout->addWidget(mainwidget, 1, 0, 1, 1);

    groupBox_2 = new QGroupBox(doceditfrm);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
    groupBox_2->setSizePolicy(sizePolicy);
    groupBox_2->setMinimumSize(QSize(761, 201));
    groupBox_2->setMaximumSize(QSize(761, 201));
    widget = new QWidget(groupBox_2);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(10, 7, 741, 191));
    gridLayout5 = new QGridLayout(widget);
#ifndef Q_OS_MAC
    gridLayout5->setSpacing(6);
#endif
    gridLayout5->setMargin(0);
    gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
    gridLayout6 = new QGridLayout();
#ifndef Q_OS_MAC
    gridLayout6->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout6->setMargin(0);
#endif
    gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
    cmbdoc = new QComboBox(widget);
    cmbdoc->setObjectName(QString::fromUtf8("cmbdoc"));

    gridLayout6->addWidget(cmbdoc, 0, 1, 1, 1);

    hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout3->setSpacing(6);
#endif
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    btnclearsearch = new QPushButton(widget);
    btnclearsearch->setObjectName(QString::fromUtf8("btnclearsearch"));
    btnclearsearch->setMinimumSize(QSize(26, 26));
    btnclearsearch->setMaximumSize(QSize(26, 26));
    btnclearsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/kill.png")));

    hboxLayout3->addWidget(btnclearsearch);

    label_4 = new QLabel(widget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    hboxLayout3->addWidget(label_4);

    lblID = new QLabel(widget);
    lblID->setObjectName(QString::fromUtf8("lblID"));

    hboxLayout3->addWidget(lblID);


    gridLayout6->addLayout(hboxLayout3, 3, 2, 1, 2);

    label_2 = new QLabel(widget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setMaximumSize(QSize(81, 16777215));

    gridLayout6->addWidget(label_2, 1, 0, 1, 1);

    label_6 = new QLabel(widget);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setMaximumSize(QSize(81, 16777215));

    gridLayout6->addWidget(label_6, 4, 0, 1, 1);


    gridLayout6->addItem(new QSpacerItem(20, 82, QSizePolicy::Minimum, QSizePolicy::Fixed), 2, 0, 2, 1);

    txtdoccount = new QLineEdit(widget);
    txtdoccount->setObjectName(QString::fromUtf8("txtdoccount"));
    txtdoccount->setMinimumSize(QSize(256, 22));
    txtdoccount->setMaximumSize(QSize(16777215, 22));

    gridLayout6->addWidget(txtdoccount, 4, 1, 1, 1);


    gridLayout6->addItem(new QSpacerItem(20, 121, QSizePolicy::Minimum, QSizePolicy::Fixed), 0, 3, 3, 1);

    btnsearchaddr = new QPushButton(widget);
    btnsearchaddr->setObjectName(QString::fromUtf8("btnsearchaddr"));
    btnsearchaddr->setMinimumSize(QSize(26, 26));
    btnsearchaddr->setMaximumSize(QSize(26, 26));
    btnsearchaddr->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));

    gridLayout6->addWidget(btnsearchaddr, 1, 2, 1, 1);


    gridLayout6->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 2, 1, 1);


    gridLayout6->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 2, 2, 1, 1);

    boxaddress = new QTextEdit(widget);
    boxaddress->setObjectName(QString::fromUtf8("boxaddress"));
    boxaddress->setMinimumSize(QSize(256, 113));

    gridLayout6->addWidget(boxaddress, 1, 1, 3, 1);


    gridLayout6->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 4, 2, 1, 2);

    label = new QLabel(widget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setMaximumSize(QSize(81, 16777215));

    gridLayout6->addWidget(label, 0, 0, 1, 1);


    gridLayout5->addLayout(gridLayout6, 0, 0, 1, 1);

    gridLayout7 = new QGridLayout();
#ifndef Q_OS_MAC
    gridLayout7->setSpacing(6);
#endif
    gridLayout7->setMargin(0);
    gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));

    gridLayout7->addItem(new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Fixed), 1, 0, 1, 1);

    gridLayout8 = new QGridLayout();
#ifndef Q_OS_MAC
    gridLayout8->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout8->setMargin(0);
#endif
    gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
    boxdate = new QDateEdit(widget);
    boxdate->setObjectName(QString::fromUtf8("boxdate"));

    gridLayout8->addWidget(boxdate, 1, 2, 1, 1);

    label_3 = new QLabel(widget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout8->addWidget(label_3, 1, 1, 1, 1);


    gridLayout8->addItem(new QSpacerItem(129, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, 0, 1, 1);

    hboxLayout4 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout4->setSpacing(6);
#endif
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));

    hboxLayout4->addItem(new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    btnnew = new QPushButton(widget);
    btnnew->setObjectName(QString::fromUtf8("btnnew"));
    sizePolicy.setHeightForWidth(btnnew->sizePolicy().hasHeightForWidth());
    btnnew->setSizePolicy(sizePolicy);
    btnnew->setIcon(QIcon(QString::fromUtf8(":/images/images/filenew.png")));
    btnnew->setIconSize(QSize(22, 22));

    hboxLayout4->addWidget(btnnew);

    btnopen = new QPushButton(widget);
    btnopen->setObjectName(QString::fromUtf8("btnopen"));
    sizePolicy.setHeightForWidth(btnopen->sizePolicy().hasHeightForWidth());
    btnopen->setSizePolicy(sizePolicy);
    btnopen->setIcon(QIcon(QString::fromUtf8(":/images/images/fileopen.png")));
    btnopen->setIconSize(QSize(22, 22));

    hboxLayout4->addWidget(btnopen);

    btnsave = new QPushButton(widget);
    btnsave->setObjectName(QString::fromUtf8("btnsave"));
    sizePolicy.setHeightForWidth(btnsave->sizePolicy().hasHeightForWidth());
    btnsave->setSizePolicy(sizePolicy);
    btnsave->setIcon(QIcon(QString::fromUtf8(":/images/images/filesave.png")));
    btnsave->setIconSize(QSize(22, 22));

    hboxLayout4->addWidget(btnsave);

    btnprint = new QPushButton(widget);
    btnprint->setObjectName(QString::fromUtf8("btnprint"));
    sizePolicy.setHeightForWidth(btnprint->sizePolicy().hasHeightForWidth());
    btnprint->setSizePolicy(sizePolicy);
    btnprint->setIcon(QIcon(QString::fromUtf8(":/images/images/fileprint.png")));
    btnprint->setIconSize(QSize(22, 22));

    hboxLayout4->addWidget(btnprint);


    hboxLayout4->addItem(new QSpacerItem(21, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));

    btncomplete = new QPushButton(widget);
    btncomplete->setObjectName(QString::fromUtf8("btncomplete"));
    sizePolicy.setHeightForWidth(btncomplete->sizePolicy().hasHeightForWidth());
    btncomplete->setSizePolicy(sizePolicy);
    btncomplete->setIcon(QIcon(QString::fromUtf8(":/images/images/button_ok.png")));
    btncomplete->setIconSize(QSize(22, 22));

    hboxLayout4->addWidget(btncomplete);


    gridLayout8->addLayout(hboxLayout4, 0, 0, 1, 3);


    gridLayout7->addLayout(gridLayout8, 0, 0, 1, 1);


    gridLayout5->addLayout(gridLayout7, 0, 1, 1, 1);


    gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);


    retranslateUi(doceditfrm);

    mainwidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(doceditfrm);
    } // setupUi

    void retranslateUi(QWidget *doceditfrm)
    {
    doceditfrm->setWindowTitle(QApplication::translate("doceditfrm", "Documents...", 0, QApplication::UnicodeUTF8));
    groupBox_3->setTitle(QString());
    btnclose->setText(QApplication::translate("doceditfrm", "&Close", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("doceditfrm", "User:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("doceditfrm", "-", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QString());
    label_13->setText(QApplication::translate("doceditfrm", "Total incl. VAT:", 0, QApplication::UnicodeUTF8));
    btncalc->setText(QApplication::translate("doceditfrm", "C&alc", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("doceditfrm", "VAT:", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("doceditfrm", "Total excl. VAT:", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("doceditfrm", "%", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("doceditfrm", "Discount:", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("doceditfrm", "Total:", 0, QApplication::UnicodeUTF8));
    label_20->setText(QApplication::translate("doceditfrm", "Salutation:", 0, QApplication::UnicodeUTF8));
    label_21->setText(QApplication::translate("doceditfrm", "Other informations:", 0, QApplication::UnicodeUTF8));
    mainwidget->setTabText(mainwidget->indexOf(tab1), QApplication::translate("doceditfrm", "Introduction", 0, QApplication::UnicodeUTF8));
    if (tabmain->columnCount() < 12)
        tabmain->setColumnCount(12);

    QTableWidgetItem *__colItem = new QTableWidgetItem();
    __colItem->setText(QApplication::translate("doceditfrm", "Pos", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(0, __colItem);

    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    __colItem1->setText(QApplication::translate("doceditfrm", "Label", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(1, __colItem1);

    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    __colItem2->setText(QString());
    __colItem2->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
    tabmain->setHorizontalHeaderItem(2, __colItem2);

    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    __colItem3->setText(QApplication::translate("doceditfrm", "Description", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(3, __colItem3);

    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    __colItem4->setText(QApplication::translate("doceditfrm", "Quantity", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(4, __colItem4);

    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    __colItem5->setText(QApplication::translate("doceditfrm", "Unit", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(5, __colItem5);

    QTableWidgetItem *__colItem6 = new QTableWidgetItem();
    __colItem6->setText(QApplication::translate("doceditfrm", "Price/Unit", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(6, __colItem6);

    QTableWidgetItem *__colItem7 = new QTableWidgetItem();
    __colItem7->setText(QApplication::translate("doceditfrm", "Price", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(7, __colItem7);

    QTableWidgetItem *__colItem8 = new QTableWidgetItem();
    __colItem8->setText(QApplication::translate("doceditfrm", "VAT", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(8, __colItem8);

    QTableWidgetItem *__colItem9 = new QTableWidgetItem();
    __colItem9->setText(QApplication::translate("doceditfrm", "actquantity", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(9, __colItem9);

    QTableWidgetItem *__colItem10 = new QTableWidgetItem();
    __colItem10->setText(QApplication::translate("doceditfrm", "minquantity", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(10, __colItem10);

    QTableWidgetItem *__colItem11 = new QTableWidgetItem();
    __colItem11->setText(QApplication::translate("doceditfrm", "artID", 0, QApplication::UnicodeUTF8));
    tabmain->setHorizontalHeaderItem(11, __colItem11);
    mainwidget->setTabText(mainwidget->indexOf(tab2), QApplication::translate("doceditfrm", "Positions", 0, QApplication::UnicodeUTF8));
    mainwidget->setTabText(mainwidget->indexOf(tab3), QApplication::translate("doceditfrm", "Comments", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QString());
    btnclearsearch->setText(QString());
    label_4->setText(QApplication::translate("doceditfrm", "Customer ID:", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("doceditfrm", "-", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("doceditfrm", "Customer:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("doceditfrm", "Document #:", 0, QApplication::UnicodeUTF8));
    txtdoccount->setText(QString());
    btnsearchaddr->setText(QString());
    label->setText(QApplication::translate("doceditfrm", "Document:", 0, QApplication::UnicodeUTF8));
    boxdate->setDisplayFormat(QApplication::translate("doceditfrm", "dd.MM.yyyy", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("doceditfrm", "Date:", 0, QApplication::UnicodeUTF8));
    btnnew->setText(QString());
    btnopen->setText(QString());
    btnsave->setText(QString());
    btnprint->setText(QString());
    btncomplete->setText(QString());
    Q_UNUSED(doceditfrm);
    } // retranslateUi

};

namespace Ui {
    class doceditfrm: public Ui_doceditfrm {};
} // namespace Ui

#endif // UI_DOCEDITFRM_H
