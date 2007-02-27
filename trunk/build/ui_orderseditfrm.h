/********************************************************************************
** Form generated from reading ui file 'orderseditfrm.ui'
**
** Created: Tue Feb 27 17:21:49 2007
**      by: Qt User Interface Compiler version 4.2.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ORDERSEDITFRM_H
#define UI_ORDERSEDITFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

class Ui_orderseditfrm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *btnclearsearch;
    QPushButton *btnsearch;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *btncancel;
    QSpacerItem *spacerItem;
    QPushButton *btnok;
    QLineEdit *txtordernr;
    QComboBox *cmbstock;
    QLineEdit *txtlabel;
    QTextEdit *txtdescription;
    QLineEdit *txtquantity;
    QComboBox *cmbsupplier;
    QLineEdit *txtprice;
    QComboBox *cmbcurrency;
    QTextEdit *txtcomments;
    QLabel *lbldbid;

    void setupUi(QDialog *orderseditfrm)
    {
    orderseditfrm->setObjectName(QString::fromUtf8("orderseditfrm"));
    orderseditfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    label = new QLabel(orderseditfrm);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 10, 56, 17));
    label_2 = new QLabel(orderseditfrm);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 40, 56, 17));
    label_3 = new QLabel(orderseditfrm);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(10, 70, 56, 17));
    label_4 = new QLabel(orderseditfrm);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(10, 100, 121, 17));
    btnclearsearch = new QPushButton(orderseditfrm);
    btnclearsearch->setObjectName(QString::fromUtf8("btnclearsearch"));
    btnclearsearch->setGeometry(QRect(380, 70, 21, 21));
    btnclearsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/kill.png")));
    btnsearch = new QPushButton(orderseditfrm);
    btnsearch->setObjectName(QString::fromUtf8("btnsearch"));
    btnsearch->setGeometry(QRect(350, 70, 21, 21));
    btnsearch->setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag2.png")));
    label_5 = new QLabel(orderseditfrm);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(10, 250, 101, 17));
    label_6 = new QLabel(orderseditfrm);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(10, 280, 101, 17));
    label_7 = new QLabel(orderseditfrm);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setGeometry(QRect(10, 310, 56, 17));
    label_8 = new QLabel(orderseditfrm);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setGeometry(QRect(10, 340, 91, 17));
    layoutWidget = new QWidget(orderseditfrm);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(10, 460, 561, 33));
    hboxLayout = new QHBoxLayout(layoutWidget);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    btncancel = new QPushButton(layoutWidget);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));

    hboxLayout->addWidget(btncancel);

    spacerItem = new QSpacerItem(381, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    btnok = new QPushButton(layoutWidget);
    btnok->setObjectName(QString::fromUtf8("btnok"));

    hboxLayout->addWidget(btnok);

    txtordernr = new QLineEdit(orderseditfrm);
    txtordernr->setObjectName(QString::fromUtf8("txtordernr"));
    txtordernr->setGeometry(QRect(121, 12, 127, 22));
    cmbstock = new QComboBox(orderseditfrm);
    cmbstock->setObjectName(QString::fromUtf8("cmbstock"));
    cmbstock->setGeometry(QRect(121, 42, 219, 22));
    txtlabel = new QLineEdit(orderseditfrm);
    txtlabel->setObjectName(QString::fromUtf8("txtlabel"));
    txtlabel->setGeometry(QRect(121, 71, 219, 22));
    txtdescription = new QTextEdit(orderseditfrm);
    txtdescription->setObjectName(QString::fromUtf8("txtdescription"));
    txtdescription->setGeometry(QRect(10, 120, 561, 111));
    txtquantity = new QLineEdit(orderseditfrm);
    txtquantity->setObjectName(QString::fromUtf8("txtquantity"));
    txtquantity->setGeometry(QRect(120, 250, 127, 22));
    cmbsupplier = new QComboBox(orderseditfrm);
    cmbsupplier->setObjectName(QString::fromUtf8("cmbsupplier"));
    cmbsupplier->setGeometry(QRect(120, 280, 281, 22));
    txtprice = new QLineEdit(orderseditfrm);
    txtprice->setObjectName(QString::fromUtf8("txtprice"));
    txtprice->setGeometry(QRect(120, 310, 127, 22));
    cmbcurrency = new QComboBox(orderseditfrm);
    cmbcurrency->setObjectName(QString::fromUtf8("cmbcurrency"));
    cmbcurrency->setGeometry(QRect(260, 310, 79, 22));
    txtcomments = new QTextEdit(orderseditfrm);
    txtcomments->setObjectName(QString::fromUtf8("txtcomments"));
    txtcomments->setGeometry(QRect(10, 360, 561, 94));
    lbldbid = new QLabel(orderseditfrm);
    lbldbid->setObjectName(QString::fromUtf8("lbldbid"));
    lbldbid->setGeometry(QRect(510, 10, 56, 17));
    lbldbid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    retranslateUi(orderseditfrm);

    QSize size(577, 497);
    size = size.expandedTo(orderseditfrm->minimumSizeHint());
    orderseditfrm->resize(size);

    QObject::connect(btnok, SIGNAL(clicked()), orderseditfrm, SLOT(accept()));
    QObject::connect(btncancel, SIGNAL(clicked()), orderseditfrm, SLOT(reject()));

    QMetaObject::connectSlotsByName(orderseditfrm);
    } // setupUi

    void retranslateUi(QDialog *orderseditfrm)
    {
    orderseditfrm->setWindowTitle(QApplication::translate("orderseditfrm", "Orders...", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("orderseditfrm", "Order #:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("orderseditfrm", "Stock:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("orderseditfrm", "Label:", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("orderseditfrm", "Description:", 0, QApplication::UnicodeUTF8));
    btnclearsearch->setText(QString());
    btnsearch->setText(QString());
    label_5->setText(QApplication::translate("orderseditfrm", "Quantity:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("orderseditfrm", "Supplier:", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("orderseditfrm", "Price:", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("orderseditfrm", "Comments:", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("orderseditfrm", "Cancel", 0, QApplication::UnicodeUTF8));
    btnok->setText(QApplication::translate("orderseditfrm", "OK", 0, QApplication::UnicodeUTF8));
    cmbcurrency->clear();
    cmbcurrency->addItem(QApplication::translate("orderseditfrm", "CHF", 0, QApplication::UnicodeUTF8));
    cmbcurrency->addItem(QApplication::translate("orderseditfrm", "EUR", 0, QApplication::UnicodeUTF8));
    cmbcurrency->addItem(QApplication::translate("orderseditfrm", "USD", 0, QApplication::UnicodeUTF8));
    lbldbid->setText(QString());
    Q_UNUSED(orderseditfrm);
    } // retranslateUi

};

namespace Ui {
    class orderseditfrm: public Ui_orderseditfrm {};
} // namespace Ui

#endif // UI_ORDERSEDITFRM_H
