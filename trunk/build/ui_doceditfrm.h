/********************************************************************************
** Form generated from reading ui file 'doceditfrm.ui'
**
** Created: Tue Feb 27 17:21:50 2007
**      by: Qt User Interface Compiler version 4.2.0
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
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

class Ui_doceditfrm
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnclearsearch;
    QLabel *label_3;
    QPushButton *btnsearchaddr;
    QLabel *label_6;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *btnprint;
    QPushButton *btnsave;
    QPushButton *btncomplete;
    QSpacerItem *spacerItem;
    QPushButton *btnnew;
    QPushButton *btnopen;
    QLabel *label_4;
    QPushButton *btnclose;
    QLabel *label_5;
    QLabel *lbluser;
    QComboBox *cmbdoc;
    QLineEdit *txtdoccount;
    QLabel *lblID;
    QDateEdit *boxdate;
    QGroupBox *groupBox;
    QFrame *line_5;
    QLabel *label_13;
    QFrame *line;
    QLabel *label_9;
    QFrame *line_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_10;
    QPushButton *btnvat;
    QLabel *label_19;
    QLineEdit *boxtot;
    QLineEdit *boxdiscount;
    QLineEdit *boxvat;
    QLineEdit *boxtot_excl;
    QLineEdit *boxtot_incl;
    QPushButton *btncalc;
    QTabWidget *mainwidget;
    QWidget *tab1;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *txtsalutation;
    QTextEdit *boxotherinfo;
    QWidget *tab2;
    QTableWidget *tabmain;
    QWidget *tab3;
    QTextEdit *boxcomments;
    QTextEdit *boxaddress;

    void setupUi(QWidget *doceditfrm)
    {
    doceditfrm->setObjectName(QString::fromUtf8("doceditfrm"));
    doceditfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/wordprocessing.png")));
    label = new QLabel(doceditfrm);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 10, 91, 17));
    label_2 = new QLabel(doceditfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 60, 91, 21));
    btnclearsearch = new QPushButton(doceditfrm);
    btnclearsearch->setObjectName(QString::fromUtf8("btnclearsearch"));
    btnclearsearch->setGeometry(QRect(340, 140, 21, 21));
    btnclearsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/kill.png")));
    label_3 = new QLabel(doceditfrm);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(570, 60, 56, 21));
    btnsearchaddr = new QPushButton(doceditfrm);
    btnsearchaddr->setObjectName(QString::fromUtf8("btnsearchaddr"));
    btnsearchaddr->setGeometry(QRect(340, 60, 21, 21));
    btnsearchaddr->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
    label_6 = new QLabel(doceditfrm);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(10, 170, 91, 21));
    widget = new QWidget(doceditfrm);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(520, 10, 233, 34));
    gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(0);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    btnprint = new QPushButton(widget);
    btnprint->setObjectName(QString::fromUtf8("btnprint"));
    btnprint->setIcon(QIcon(QString::fromUtf8(":/images/images/fileprint.png")));
    btnprint->setIconSize(QSize(22, 22));

    gridLayout->addWidget(btnprint, 0, 3, 1, 1);

    btnsave = new QPushButton(widget);
    btnsave->setObjectName(QString::fromUtf8("btnsave"));
    btnsave->setIcon(QIcon(QString::fromUtf8(":/images/images/filesave.png")));
    btnsave->setIconSize(QSize(22, 22));

    gridLayout->addWidget(btnsave, 0, 2, 1, 1);

    btncomplete = new QPushButton(widget);
    btncomplete->setObjectName(QString::fromUtf8("btncomplete"));
    btncomplete->setIcon(QIcon(QString::fromUtf8(":/images/images/button_ok.png")));
    btncomplete->setIconSize(QSize(22, 22));

    gridLayout->addWidget(btncomplete, 0, 5, 1, 1);

    spacerItem = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem, 0, 4, 1, 1);

    btnnew = new QPushButton(widget);
    btnnew->setObjectName(QString::fromUtf8("btnnew"));
    btnnew->setIcon(QIcon(QString::fromUtf8(":/images/images/filenew.png")));
    btnnew->setIconSize(QSize(22, 22));

    gridLayout->addWidget(btnnew, 0, 0, 1, 1);

    btnopen = new QPushButton(widget);
    btnopen->setObjectName(QString::fromUtf8("btnopen"));
    btnopen->setIcon(QIcon(QString::fromUtf8(":/images/images/fileopen.png")));
    btnopen->setIconSize(QSize(22, 22));

    gridLayout->addWidget(btnopen, 0, 1, 1, 1);

    label_4 = new QLabel(doceditfrm);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(380, 140, 101, 17));
    btnclose = new QPushButton(doceditfrm);
    btnclose->setObjectName(QString::fromUtf8("btnclose"));
    btnclose->setGeometry(QRect(10, 650, 80, 27));
    label_5 = new QLabel(doceditfrm);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(100, 650, 56, 31));
    lbluser = new QLabel(doceditfrm);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));
    lbluser->setGeometry(QRect(180, 650, 141, 31));
    cmbdoc = new QComboBox(doceditfrm);
    cmbdoc->setObjectName(QString::fromUtf8("cmbdoc"));
    cmbdoc->setGeometry(QRect(110, 10, 221, 22));
    txtdoccount = new QLineEdit(doceditfrm);
    txtdoccount->setObjectName(QString::fromUtf8("txtdoccount"));
    txtdoccount->setGeometry(QRect(110, 170, 221, 22));
    lblID = new QLabel(doceditfrm);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(490, 140, 56, 17));
    boxdate = new QDateEdit(doceditfrm);
    boxdate->setObjectName(QString::fromUtf8("boxdate"));
    boxdate->setGeometry(QRect(640, 60, 111, 22));
    groupBox = new QGroupBox(doceditfrm);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(480, 510, 281, 171));
    line_5 = new QFrame(groupBox);
    line_5->setObjectName(QString::fromUtf8("line_5"));
    line_5->setGeometry(QRect(10, 130, 265, 2));
    line_5->setFrameShape(QFrame::HLine);
    line_5->setFrameShadow(QFrame::Sunken);
    label_13 = new QLabel(groupBox);
    label_13->setObjectName(QString::fromUtf8("label_13"));
    label_13->setGeometry(QRect(20, 110, 121, 17));
    line = new QFrame(groupBox);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(10, 100, 265, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    label_9 = new QLabel(groupBox);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(20, 10, 121, 17));
    line_2 = new QFrame(groupBox);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setGeometry(QRect(10, 132, 265, 2));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);
    label_11 = new QLabel(groupBox);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    label_11->setGeometry(QRect(20, 56, 121, 21));
    label_12 = new QLabel(groupBox);
    label_12->setObjectName(QString::fromUtf8("label_12"));
    label_12->setGeometry(QRect(20, 80, 121, 17));
    label_10 = new QLabel(groupBox);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(70, 30, 81, 21));
    label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    btnvat = new QPushButton(groupBox);
    btnvat->setObjectName(QString::fromUtf8("btnvat"));
    btnvat->setGeometry(QRect(130, 78, 21, 20));
    btnvat->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
    label_19 = new QLabel(groupBox);
    label_19->setObjectName(QString::fromUtf8("label_19"));
    label_19->setGeometry(QRect(250, 34, 21, 17));
    label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    boxtot = new QLineEdit(groupBox);
    boxtot->setObjectName(QString::fromUtf8("boxtot"));
    boxtot->setGeometry(QRect(160, 10, 113, 21));
    boxdiscount = new QLineEdit(groupBox);
    boxdiscount->setObjectName(QString::fromUtf8("boxdiscount"));
    boxdiscount->setGeometry(QRect(160, 32, 80, 21));
    boxdiscount->setAlignment(Qt::AlignRight);
    boxvat = new QLineEdit(groupBox);
    boxvat->setObjectName(QString::fromUtf8("boxvat"));
    boxvat->setGeometry(QRect(160, 77, 113, 21));
    boxtot_excl = new QLineEdit(groupBox);
    boxtot_excl->setObjectName(QString::fromUtf8("boxtot_excl"));
    boxtot_excl->setGeometry(QRect(160, 54, 113, 21));
    boxtot_incl = new QLineEdit(groupBox);
    boxtot_incl->setObjectName(QString::fromUtf8("boxtot_incl"));
    boxtot_incl->setGeometry(QRect(160, 107, 113, 21));
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    boxtot_incl->setFont(font);
    btncalc = new QPushButton(groupBox);
    btncalc->setObjectName(QString::fromUtf8("btncalc"));
    btncalc->setGeometry(QRect(180, 140, 91, 27));
    mainwidget = new QTabWidget(doceditfrm);
    mainwidget->setObjectName(QString::fromUtf8("mainwidget"));
    mainwidget->setGeometry(QRect(10, 200, 751, 301));
    tab1 = new QWidget();
    tab1->setObjectName(QString::fromUtf8("tab1"));
    label_20 = new QLabel(tab1);
    label_20->setObjectName(QString::fromUtf8("label_20"));
    label_20->setGeometry(QRect(10, 10, 111, 21));
    label_21 = new QLabel(tab1);
    label_21->setObjectName(QString::fromUtf8("label_21"));
    label_21->setGeometry(QRect(10, 40, 181, 17));
    txtsalutation = new QLineEdit(tab1);
    txtsalutation->setObjectName(QString::fromUtf8("txtsalutation"));
    txtsalutation->setGeometry(QRect(130, 10, 611, 21));
    boxotherinfo = new QTextEdit(tab1);
    boxotherinfo->setObjectName(QString::fromUtf8("boxotherinfo"));
    boxotherinfo->setGeometry(QRect(10, 60, 731, 201));
    mainwidget->addTab(tab1, QApplication::translate("doceditfrm", "Introduction", 0, QApplication::UnicodeUTF8));
    tab2 = new QWidget();
    tab2->setObjectName(QString::fromUtf8("tab2"));
    tabmain = new QTableWidget(tab2);
    tabmain->setObjectName(QString::fromUtf8("tabmain"));
    tabmain->setGeometry(QRect(10, 10, 731, 251));
    QFont font1;
    font1.setPointSize(8);
    tabmain->setFont(font1);
    mainwidget->addTab(tab2, QApplication::translate("doceditfrm", "Positions", 0, QApplication::UnicodeUTF8));
    tab3 = new QWidget();
    tab3->setObjectName(QString::fromUtf8("tab3"));
    boxcomments = new QTextEdit(tab3);
    boxcomments->setObjectName(QString::fromUtf8("boxcomments"));
    boxcomments->setGeometry(QRect(10, 10, 731, 251));
    mainwidget->addTab(tab3, QApplication::translate("doceditfrm", "Comments", 0, QApplication::UnicodeUTF8));
    boxaddress = new QTextEdit(doceditfrm);
    boxaddress->setObjectName(QString::fromUtf8("boxaddress"));
    boxaddress->setGeometry(QRect(110, 60, 221, 101));

    retranslateUi(doceditfrm);

    QSize size(773, 685);
    size = size.expandedTo(doceditfrm->minimumSizeHint());
    doceditfrm->resize(size);


    mainwidget->setCurrentIndex(1);


    QMetaObject::connectSlotsByName(doceditfrm);
    } // setupUi

    void retranslateUi(QWidget *doceditfrm)
    {
    doceditfrm->setWindowTitle(QApplication::translate("doceditfrm", "Documents...", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("doceditfrm", "Document:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("doceditfrm", "Customer:", 0, QApplication::UnicodeUTF8));
    btnclearsearch->setText(QString());
    label_3->setText(QApplication::translate("doceditfrm", "Date:", 0, QApplication::UnicodeUTF8));
    btnsearchaddr->setText(QString());
    label_6->setText(QApplication::translate("doceditfrm", "Document #:", 0, QApplication::UnicodeUTF8));
    btnprint->setText(QString());
    btnsave->setText(QString());
    btncomplete->setText(QString());
    btnnew->setText(QString());
    btnopen->setText(QString());
    label_4->setText(QApplication::translate("doceditfrm", "Customer ID:", 0, QApplication::UnicodeUTF8));
    btnclose->setText(QApplication::translate("doceditfrm", "&Close", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("doceditfrm", "User:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("doceditfrm", "-", 0, QApplication::UnicodeUTF8));
    txtdoccount->setText(QString());
    lblID->setText(QApplication::translate("doceditfrm", "-", 0, QApplication::UnicodeUTF8));
    boxdate->setDisplayFormat(QApplication::translate("doceditfrm", "dd.MM.yyyy", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QString());
    label_13->setText(QApplication::translate("doceditfrm", "Total incl. VAT:", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("doceditfrm", "Total:", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("doceditfrm", "Total excl. VAT:", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("doceditfrm", "VAT:", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("doceditfrm", "Discount:", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("doceditfrm", "%", 0, QApplication::UnicodeUTF8));
    btncalc->setText(QApplication::translate("doceditfrm", "C&alc", 0, QApplication::UnicodeUTF8));
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
    Q_UNUSED(doceditfrm);
    } // retranslateUi

};

namespace Ui {
    class doceditfrm: public Ui_doceditfrm {};
} // namespace Ui

#endif // UI_DOCEDITFRM_H
