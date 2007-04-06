/********************************************************************************
** Form generated from reading ui file 'dataeditfrm.ui'
**
** Created: Thu Apr 5 22:13:13 2007
**      by: Qt User Interface Compiler version 4.3.0beta
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DATAEDITFRM_H
#define UI_DATAEDITFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

class Ui_dataeditfrm
{
public:
    QLabel *label_19;
    QLabel *lblcreated;
    QLabel *label_21;
    QLabel *lblmodified;
    QLabel *label_12;
    QLabel *lblprofit;
    QLineEdit *txtunit;
    QLineEdit *txtstock;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label_14;
    QPushButton *btncancel;
    QTabWidget *maintab;
    QWidget *tab_1;
    QGridLayout *gridLayout;
    QTableWidget *tabsuppliers;
    QWidget *tab_2;
    QLineEdit *txtweight;
    QLabel *label_27;
    QLabel *label_26;
    QLabel *label_25;
    QLabel *label_24;
    QLabel *label_29;
    QLabel *label_23;
    QLineEdit *txtpackage;
    QLineEdit *txtstockpos;
    QLabel *label_28;
    QDateEdit *txtsalesdate;
    QComboBox *cmbvat;
    QCheckBox *chkactive;
    QWidget *tab_3;
    QLabel *label_30;
    QLineEdit *txtwebname;
    QLineEdit *txtwebimage;
    QLineEdit *txtweburl;
    QLabel *label_31;
    QLabel *label_32;
    QWidget *tab_4;
    QGridLayout *gridLayout1;
    QTextEdit *txtcomments;
    QLabel *lblmargin;
    QLineEdit *txtlabel;
    QLabel *lblID;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *lbldatatab;
    QLineEdit *txtpurchaseprice;
    QLineEdit *txtsellprice;
    QTextEdit *txtdescription;
    QLineEdit *txtminquantity;
    QLineEdit *txtorderquantity;
    QPushButton *btnok;

    void setupUi(QDialog *dataeditfrm)
    {
    if (dataeditfrm->objectName().isEmpty())
        dataeditfrm->setObjectName(QString::fromUtf8("dataeditfrm"));
    QSize size(776, 496);
    size = size.expandedTo(dataeditfrm->minimumSizeHint());
    dataeditfrm->resize(size);
    dataeditfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/kfm32x32.png")));
    label_19 = new QLabel(dataeditfrm);
    label_19->setObjectName(QString::fromUtf8("label_19"));
    label_19->setGeometry(QRect(240, 460, 51, 31));
    lblcreated = new QLabel(dataeditfrm);
    lblcreated->setObjectName(QString::fromUtf8("lblcreated"));
    lblcreated->setGeometry(QRect(300, 460, 81, 31));
    label_21 = new QLabel(dataeditfrm);
    label_21->setObjectName(QString::fromUtf8("label_21"));
    label_21->setGeometry(QRect(470, 460, 54, 31));
    lblmodified = new QLabel(dataeditfrm);
    lblmodified->setObjectName(QString::fromUtf8("lblmodified"));
    lblmodified->setGeometry(QRect(530, 460, 91, 31));
    label_12 = new QLabel(dataeditfrm);
    label_12->setObjectName(QString::fromUtf8("label_12"));
    label_12->setGeometry(QRect(245, 422, 24, 27));
    lblprofit = new QLabel(dataeditfrm);
    lblprofit->setObjectName(QString::fromUtf8("lblprofit"));
    lblprofit->setGeometry(QRect(141, 388, 98, 28));
    txtunit = new QLineEdit(dataeditfrm);
    txtunit->setObjectName(QString::fromUtf8("txtunit"));
    txtunit->setGeometry(QRect(141, 265, 98, 22));
    txtstock = new QLineEdit(dataeditfrm);
    txtstock->setObjectName(QString::fromUtf8("txtstock"));
    txtstock->setGeometry(QRect(141, 203, 98, 22));
    label_11 = new QLabel(dataeditfrm);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    label_11->setGeometry(QRect(17, 387, 111, 26));
    label_5 = new QLabel(dataeditfrm);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(17, 207, 111, 17));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
    label_5->setSizePolicy(sizePolicy);
    label_5->setMinimumSize(QSize(111, 0));
    label_5->setMaximumSize(QSize(111, 16777215));
    label_6 = new QLabel(dataeditfrm);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(17, 230, 111, 25));
    label_8 = new QLabel(dataeditfrm);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setGeometry(QRect(17, 293, 111, 25));
    label_13 = new QLabel(dataeditfrm);
    label_13->setObjectName(QString::fromUtf8("label_13"));
    label_13->setGeometry(QRect(17, 419, 111, 25));
    label_7 = new QLabel(dataeditfrm);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setGeometry(QRect(17, 261, 111, 26));
    label_9 = new QLabel(dataeditfrm);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(17, 324, 111, 26));
    label_10 = new QLabel(dataeditfrm);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(17, 356, 111, 25));
    label_16 = new QLabel(dataeditfrm);
    label_16->setObjectName(QString::fromUtf8("label_16"));
    label_16->setGeometry(QRect(245, 326, 31, 25));
    label_15 = new QLabel(dataeditfrm);
    label_15->setObjectName(QString::fromUtf8("label_15"));
    label_15->setGeometry(QRect(245, 357, 31, 25));
    label_14 = new QLabel(dataeditfrm);
    label_14->setObjectName(QString::fromUtf8("label_14"));
    label_14->setGeometry(QRect(245, 388, 31, 28));
    btncancel = new QPushButton(dataeditfrm);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(10, 460, 75, 27));
    maintab = new QTabWidget(dataeditfrm);
    maintab->setObjectName(QString::fromUtf8("maintab"));
    maintab->setGeometry(QRect(285, 200, 481, 251));
    tab_1 = new QWidget();
    tab_1->setObjectName(QString::fromUtf8("tab_1"));
    gridLayout = new QGridLayout(tab_1);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout->setMargin(9);
#endif
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    tabsuppliers = new QTableWidget(tab_1);
    tabsuppliers->setObjectName(QString::fromUtf8("tabsuppliers"));
    tabsuppliers->setContextMenuPolicy(Qt::CustomContextMenu);
    tabsuppliers->setSelectionMode(QAbstractItemView::SingleSelection);
    tabsuppliers->setSelectionBehavior(QAbstractItemView::SelectItems);

    gridLayout->addWidget(tabsuppliers, 0, 0, 1, 1);

    maintab->addTab(tab_1, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    txtweight = new QLineEdit(tab_2);
    txtweight->setObjectName(QString::fromUtf8("txtweight"));
    txtweight->setGeometry(QRect(120, 50, 71, 25));
    label_27 = new QLabel(tab_2);
    label_27->setObjectName(QString::fromUtf8("label_27"));
    label_27->setGeometry(QRect(10, 140, 101, 21));
    label_26 = new QLabel(tab_2);
    label_26->setObjectName(QString::fromUtf8("label_26"));
    label_26->setGeometry(QRect(10, 110, 101, 21));
    label_25 = new QLabel(tab_2);
    label_25->setObjectName(QString::fromUtf8("label_25"));
    label_25->setGeometry(QRect(10, 80, 101, 21));
    label_24 = new QLabel(tab_2);
    label_24->setObjectName(QString::fromUtf8("label_24"));
    label_24->setGeometry(QRect(10, 50, 101, 21));
    label_29 = new QLabel(tab_2);
    label_29->setObjectName(QString::fromUtf8("label_29"));
    label_29->setGeometry(QRect(200, 50, 101, 21));
    label_23 = new QLabel(tab_2);
    label_23->setObjectName(QString::fromUtf8("label_23"));
    label_23->setGeometry(QRect(10, 20, 101, 21));
    txtpackage = new QLineEdit(tab_2);
    txtpackage->setObjectName(QString::fromUtf8("txtpackage"));
    txtpackage->setGeometry(QRect(120, 20, 221, 25));
    txtstockpos = new QLineEdit(tab_2);
    txtstockpos->setObjectName(QString::fromUtf8("txtstockpos"));
    txtstockpos->setGeometry(QRect(120, 170, 221, 25));
    label_28 = new QLabel(tab_2);
    label_28->setObjectName(QString::fromUtf8("label_28"));
    label_28->setGeometry(QRect(10, 170, 101, 21));
    txtsalesdate = new QDateEdit(tab_2);
    txtsalesdate->setObjectName(QString::fromUtf8("txtsalesdate"));
    txtsalesdate->setGeometry(QRect(120, 140, 110, 25));
    txtsalesdate->setMinimumSize(QSize(110, 0));
    cmbvat = new QComboBox(tab_2);
    cmbvat->setObjectName(QString::fromUtf8("cmbvat"));
    cmbvat->setGeometry(QRect(120, 80, 111, 22));
    chkactive = new QCheckBox(tab_2);
    chkactive->setObjectName(QString::fromUtf8("chkactive"));
    chkactive->setGeometry(QRect(120, 110, 82, 22));
    maintab->addTab(tab_2, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    label_30 = new QLabel(tab_3);
    label_30->setObjectName(QString::fromUtf8("label_30"));
    label_30->setGeometry(QRect(10, 20, 101, 21));
    txtwebname = new QLineEdit(tab_3);
    txtwebname->setObjectName(QString::fromUtf8("txtwebname"));
    txtwebname->setGeometry(QRect(120, 20, 221, 25));
    txtwebimage = new QLineEdit(tab_3);
    txtwebimage->setObjectName(QString::fromUtf8("txtwebimage"));
    txtwebimage->setGeometry(QRect(120, 50, 221, 25));
    txtweburl = new QLineEdit(tab_3);
    txtweburl->setObjectName(QString::fromUtf8("txtweburl"));
    txtweburl->setGeometry(QRect(120, 80, 221, 25));
    label_31 = new QLabel(tab_3);
    label_31->setObjectName(QString::fromUtf8("label_31"));
    label_31->setGeometry(QRect(10, 50, 101, 21));
    label_32 = new QLabel(tab_3);
    label_32->setObjectName(QString::fromUtf8("label_32"));
    label_32->setGeometry(QRect(10, 80, 101, 21));
    maintab->addTab(tab_3, QString());
    tab_4 = new QWidget();
    tab_4->setObjectName(QString::fromUtf8("tab_4"));
    gridLayout1 = new QGridLayout(tab_4);
#ifndef Q_OS_MAC
    gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout1->setMargin(9);
#endif
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    txtcomments = new QTextEdit(tab_4);
    txtcomments->setObjectName(QString::fromUtf8("txtcomments"));

    gridLayout1->addWidget(txtcomments, 0, 0, 1, 1);

    maintab->addTab(tab_4, QString());
    lblmargin = new QLabel(dataeditfrm);
    lblmargin->setObjectName(QString::fromUtf8("lblmargin"));
    lblmargin->setGeometry(QRect(140, 420, 98, 27));
    txtlabel = new QLineEdit(dataeditfrm);
    txtlabel->setObjectName(QString::fromUtf8("txtlabel"));
    txtlabel->setGeometry(QRect(138, 38, 305, 22));
    lblID = new QLabel(dataeditfrm);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(138, 11, 305, 20));
    label_3 = new QLabel(dataeditfrm);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(11, 37, 121, 25));
    label = new QLabel(dataeditfrm);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(11, 11, 121, 20));
    label_4 = new QLabel(dataeditfrm);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(11, 68, 121, 35));
    label_2 = new QLabel(dataeditfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(570, 10, 81, 21));
    lbldatatab = new QLabel(dataeditfrm);
    lbldatatab->setObjectName(QString::fromUtf8("lbldatatab"));
    lbldatatab->setGeometry(QRect(655, 10, 111, 20));
    txtpurchaseprice = new QLineEdit(dataeditfrm);
    txtpurchaseprice->setObjectName(QString::fromUtf8("txtpurchaseprice"));
    txtpurchaseprice->setGeometry(QRect(141, 327, 98, 22));
    txtsellprice = new QLineEdit(dataeditfrm);
    txtsellprice->setObjectName(QString::fromUtf8("txtsellprice"));
    txtsellprice->setGeometry(QRect(141, 358, 98, 22));
    txtdescription = new QTextEdit(dataeditfrm);
    txtdescription->setObjectName(QString::fromUtf8("txtdescription"));
    txtdescription->setGeometry(QRect(138, 68, 632, 122));
    txtminquantity = new QLineEdit(dataeditfrm);
    txtminquantity->setObjectName(QString::fromUtf8("txtminquantity"));
    txtminquantity->setGeometry(QRect(141, 234, 98, 22));
    txtorderquantity = new QLineEdit(dataeditfrm);
    txtorderquantity->setObjectName(QString::fromUtf8("txtorderquantity"));
    txtorderquantity->setGeometry(QRect(141, 296, 98, 22));
    btnok = new QPushButton(dataeditfrm);
    btnok->setObjectName(QString::fromUtf8("btnok"));
    btnok->setGeometry(QRect(690, 460, 75, 27));
    QWidget::setTabOrder(txtlabel, txtdescription);
    QWidget::setTabOrder(txtdescription, txtstock);
    QWidget::setTabOrder(txtstock, txtminquantity);
    QWidget::setTabOrder(txtminquantity, txtunit);
    QWidget::setTabOrder(txtunit, txtorderquantity);
    QWidget::setTabOrder(txtorderquantity, txtpurchaseprice);
    QWidget::setTabOrder(txtpurchaseprice, txtsellprice);
    QWidget::setTabOrder(txtsellprice, maintab);
    QWidget::setTabOrder(maintab, tabsuppliers);
    QWidget::setTabOrder(tabsuppliers, txtpackage);
    QWidget::setTabOrder(txtpackage, txtweight);
    QWidget::setTabOrder(txtweight, cmbvat);
    QWidget::setTabOrder(cmbvat, chkactive);
    QWidget::setTabOrder(chkactive, txtsalesdate);
    QWidget::setTabOrder(txtsalesdate, txtstockpos);
    QWidget::setTabOrder(txtstockpos, txtwebname);
    QWidget::setTabOrder(txtwebname, txtwebimage);
    QWidget::setTabOrder(txtwebimage, txtweburl);
    QWidget::setTabOrder(txtweburl, txtcomments);
    QWidget::setTabOrder(txtcomments, btnok);
    QWidget::setTabOrder(btnok, btncancel);

    retranslateUi(dataeditfrm);
    QObject::connect(btncancel, SIGNAL(released()), dataeditfrm, SLOT(reject()));

    maintab->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(dataeditfrm);
    } // setupUi

    void retranslateUi(QDialog *dataeditfrm)
    {
    dataeditfrm->setWindowTitle(QApplication::translate("dataeditfrm", "New entry...", 0, QApplication::UnicodeUTF8));
    label_19->setText(QApplication::translate("dataeditfrm", "Created:", 0, QApplication::UnicodeUTF8));
    lblcreated->setText(QApplication::translate("dataeditfrm", "-", 0, QApplication::UnicodeUTF8));
    label_21->setText(QApplication::translate("dataeditfrm", "Modified:", 0, QApplication::UnicodeUTF8));
    lblmodified->setText(QApplication::translate("dataeditfrm", "-", 0, QApplication::UnicodeUTF8));
    label_12->setText(QApplication::translate("dataeditfrm", "%", 0, QApplication::UnicodeUTF8));
    lblprofit->setText(QApplication::translate("dataeditfrm", "-", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("dataeditfrm", "Profit:", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("dataeditfrm", "Stock:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("dataeditfrm", "Min. quantity:", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("dataeditfrm", "Order quantity:", 0, QApplication::UnicodeUTF8));
    label_13->setText(QApplication::translate("dataeditfrm", "Margin:", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("dataeditfrm", "Unit:", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("dataeditfrm", "Purchase price:", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("dataeditfrm", "Sell price:", 0, QApplication::UnicodeUTF8));
    label_16->setText(QApplication::translate("dataeditfrm", "CHF", 0, QApplication::UnicodeUTF8));
    label_15->setText(QApplication::translate("dataeditfrm", "CHF", 0, QApplication::UnicodeUTF8));
    label_14->setText(QApplication::translate("dataeditfrm", "CHF", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("dataeditfrm", "Cancel", 0, QApplication::UnicodeUTF8));
    if (tabsuppliers->columnCount() < 5)
        tabsuppliers->setColumnCount(5);

    QTableWidgetItem *__colItem = new QTableWidgetItem();
    __colItem->setText(QApplication::translate("dataeditfrm", "Supplier", 0, QApplication::UnicodeUTF8));
    tabsuppliers->setHorizontalHeaderItem(0, __colItem);

    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    __colItem1->setText(QApplication::translate("dataeditfrm", "ID", 0, QApplication::UnicodeUTF8));
    tabsuppliers->setHorizontalHeaderItem(1, __colItem1);

    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    __colItem2->setText(QApplication::translate("dataeditfrm", "Purchase price", 0, QApplication::UnicodeUTF8));
    tabsuppliers->setHorizontalHeaderItem(2, __colItem2);

    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    __colItem3->setText(QApplication::translate("dataeditfrm", "Part number", 0, QApplication::UnicodeUTF8));
    tabsuppliers->setHorizontalHeaderItem(3, __colItem3);

    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    __colItem4->setText(QApplication::translate("dataeditfrm", "Comments", 0, QApplication::UnicodeUTF8));
    tabsuppliers->setHorizontalHeaderItem(4, __colItem4);
    maintab->setTabText(maintab->indexOf(tab_1), QApplication::translate("dataeditfrm", "Supplier", 0, QApplication::UnicodeUTF8));
    label_27->setText(QApplication::translate("dataeditfrm", "Sales date:", 0, QApplication::UnicodeUTF8));
    label_26->setText(QApplication::translate("dataeditfrm", "State:", 0, QApplication::UnicodeUTF8));
    label_25->setText(QApplication::translate("dataeditfrm", "VAT:", 0, QApplication::UnicodeUTF8));
    label_24->setText(QApplication::translate("dataeditfrm", "Weight:", 0, QApplication::UnicodeUTF8));
    label_29->setText(QApplication::translate("dataeditfrm", "kg", 0, QApplication::UnicodeUTF8));
    label_23->setText(QApplication::translate("dataeditfrm", "Package:", 0, QApplication::UnicodeUTF8));
    label_28->setText(QApplication::translate("dataeditfrm", "Stock position:", 0, QApplication::UnicodeUTF8));
    chkactive->setText(QApplication::translate("dataeditfrm", "Active", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab_2), QApplication::translate("dataeditfrm", "add. Informations", 0, QApplication::UnicodeUTF8));
    label_30->setText(QApplication::translate("dataeditfrm", "Web-Name:", 0, QApplication::UnicodeUTF8));
    label_31->setText(QApplication::translate("dataeditfrm", "Web-Image:", 0, QApplication::UnicodeUTF8));
    label_32->setText(QApplication::translate("dataeditfrm", "Web-URL:", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab_3), QApplication::translate("dataeditfrm", "Web", 0, QApplication::UnicodeUTF8));
    maintab->setTabText(maintab->indexOf(tab_4), QApplication::translate("dataeditfrm", "Comments", 0, QApplication::UnicodeUTF8));
    lblmargin->setText(QApplication::translate("dataeditfrm", "-", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("dataeditfrm", "-", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("dataeditfrm", "Label:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("dataeditfrm", "Entry-ID:", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("dataeditfrm", "Description:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("dataeditfrm", "Stock:", 0, QApplication::UnicodeUTF8));
    lbldatatab->setText(QApplication::translate("dataeditfrm", "-", 0, QApplication::UnicodeUTF8));
    btnok->setText(QApplication::translate("dataeditfrm", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(dataeditfrm);
    } // retranslateUi

};

namespace Ui {
    class dataeditfrm: public Ui_dataeditfrm {};
} // namespace Ui

#endif // UI_DATAEDITFRM_H
