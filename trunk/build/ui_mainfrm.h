/********************************************************************************
** Form generated from reading ui file 'mainfrm.ui'
**
** Created: Thu Apr 5 22:13:13 2007
**      by: Qt User Interface Compiler version 4.3.0beta
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINFRM_H
#define UI_MAINFRM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QToolBox>
#include <QtGui/QWidget>

class Ui_mainfrm
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *btnsettings;
    QLabel *lblmsg;
    QPushButton *btnabout;
    QPushButton *btnexit;
    QToolBox *maintoolbox;
    QWidget *page_1;
    QPushButton *btnbrowsedir;
    QWidget *page_2;
    QPushButton *btnvieworders;
    QPushButton *btninventory;
    QPushButton *btnbrowsedata;
    QWidget *page_3;
    QWidget *page_4;
    QPushButton *btnbrowsedoc;
    QPushButton *btnnewdoc;
    QWidget *page_5;
    QWidget *page_6;
    QWidget *page_7;
    QWidget *page;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *lbldb;
    QLabel *lblserver;
    QLabel *label;
    QLabel *lbluser;

    void setupUi(QMainWindow *mainfrm)
    {
    if (mainfrm->objectName().isEmpty())
        mainfrm->setObjectName(QString::fromUtf8("mainfrm"));
    QSize size(332, 553);
    size = size.expandedTo(mainfrm->minimumSizeHint());
    mainfrm->resize(size);
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mainfrm->sizePolicy().hasHeightForWidth());
    mainfrm->setSizePolicy(sizePolicy);
    mainfrm->setMinimumSize(QSize(332, 553));
    mainfrm->setMaximumSize(QSize(332, 553));
    mainfrm->setWindowIcon(QIcon(QString::fromUtf8(":/images/images/logo.png")));
    centralwidget = new QWidget(mainfrm);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    groupBox = new QGroupBox(centralwidget);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 450, 311, 91));
    btnsettings = new QPushButton(groupBox);
    btnsettings->setObjectName(QString::fromUtf8("btnsettings"));
    btnsettings->setGeometry(QRect(160, 10, 141, 30));
    btnsettings->setIcon(QIcon(QString::fromUtf8(":/images/images/package_utilities.png")));
    lblmsg = new QLabel(groupBox);
    lblmsg->setObjectName(QString::fromUtf8("lblmsg"));
    lblmsg->setGeometry(QRect(10, 10, 141, 20));
    btnabout = new QPushButton(groupBox);
    btnabout->setObjectName(QString::fromUtf8("btnabout"));
    btnabout->setGeometry(QRect(10, 50, 141, 30));
    btnabout->setIcon(QIcon(QString::fromUtf8(":/images/images/help_index.png")));
    btnexit = new QPushButton(groupBox);
    btnexit->setObjectName(QString::fromUtf8("btnexit"));
    btnexit->setGeometry(QRect(160, 50, 141, 30));
    btnexit->setIcon(QIcon(QString::fromUtf8(":/images/images/exit.png")));
    maintoolbox = new QToolBox(centralwidget);
    maintoolbox->setObjectName(QString::fromUtf8("maintoolbox"));
    maintoolbox->setGeometry(QRect(10, 10, 311, 431));
    maintoolbox->setCursor(QCursor(static_cast<Qt::CursorShape>(13)));
    maintoolbox->setAutoFillBackground(false);
    page_1 = new QWidget();
    page_1->setObjectName(QString::fromUtf8("page_1"));
    page_1->setGeometry(QRect(0, 0, 96, 26));
    btnbrowsedir = new QPushButton(page_1);
    btnbrowsedir->setObjectName(QString::fromUtf8("btnbrowsedir"));
    btnbrowsedir->setGeometry(QRect(10, 10, 251, 27));
    QPalette palette;
    QBrush brush(QColor(206, 207, 209, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Button, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    btnbrowsedir->setPalette(palette);
    btnbrowsedir->setAutoFillBackground(true);
    btnbrowsedir->setIcon(QIcon(QString::fromUtf8(":/images/images/kdmconfig.png")));
    btnbrowsedir->setCheckable(false);
    btnbrowsedir->setFlat(true);
    maintoolbox->addItem(page_1, QIcon(QString::fromUtf8(":/images/images/kdmconfig.png")), QApplication::translate("mainfrm", "Directories", 0, QApplication::UnicodeUTF8));
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    page_2->setGeometry(QRect(0, 0, 96, 26));
    btnvieworders = new QPushButton(page_2);
    btnvieworders->setObjectName(QString::fromUtf8("btnvieworders"));
    btnvieworders->setGeometry(QRect(10, 40, 251, 27));
    QPalette palette1;
    palette1.setBrush(QPalette::Active, QPalette::Button, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
    palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
    btnvieworders->setPalette(palette1);
    btnvieworders->setAutoFillBackground(true);
    btnvieworders->setIcon(QIcon(QString::fromUtf8(":/images/images/kfind.png")));
    btnvieworders->setCheckable(false);
    btnvieworders->setFlat(true);
    btninventory = new QPushButton(page_2);
    btninventory->setObjectName(QString::fromUtf8("btninventory"));
    btninventory->setGeometry(QRect(10, 70, 251, 27));
    QPalette palette2;
    palette2.setBrush(QPalette::Active, QPalette::Button, brush);
    palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
    palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
    btninventory->setPalette(palette2);
    btninventory->setAutoFillBackground(true);
    btninventory->setIcon(QIcon(QString::fromUtf8(":/images/images/kontact_todo.png")));
    btninventory->setCheckable(false);
    btninventory->setFlat(true);
    btnbrowsedata = new QPushButton(page_2);
    btnbrowsedata->setObjectName(QString::fromUtf8("btnbrowsedata"));
    btnbrowsedata->setGeometry(QRect(10, 10, 251, 27));
    QPalette palette3;
    palette3.setBrush(QPalette::Active, QPalette::Button, brush);
    palette3.setBrush(QPalette::Inactive, QPalette::Button, brush);
    palette3.setBrush(QPalette::Disabled, QPalette::Button, brush);
    btnbrowsedata->setPalette(palette3);
    btnbrowsedata->setAutoFillBackground(true);
    btnbrowsedata->setIcon(QIcon(QString::fromUtf8(":/images/images/kfm32x32.png")));
    btnbrowsedata->setCheckable(false);
    btnbrowsedata->setFlat(true);
    maintoolbox->addItem(page_2, QIcon(QString::fromUtf8(":/images/images/kfm.png")), QApplication::translate("mainfrm", "Datatables", 0, QApplication::UnicodeUTF8));
    page_3 = new QWidget();
    page_3->setObjectName(QString::fromUtf8("page_3"));
    page_3->setGeometry(QRect(0, 0, 96, 26));
    maintoolbox->addItem(page_3, QIcon(QString::fromUtf8(":/images/images/kontact_todo.png")), QApplication::translate("mainfrm", "Procedures", 0, QApplication::UnicodeUTF8));
    page_4 = new QWidget();
    page_4->setObjectName(QString::fromUtf8("page_4"));
    page_4->setGeometry(QRect(0, 0, 311, 183));
    btnbrowsedoc = new QPushButton(page_4);
    btnbrowsedoc->setObjectName(QString::fromUtf8("btnbrowsedoc"));
    btnbrowsedoc->setGeometry(QRect(10, 10, 251, 27));
    QPalette palette4;
    palette4.setBrush(QPalette::Active, QPalette::Button, brush);
    palette4.setBrush(QPalette::Inactive, QPalette::Button, brush);
    palette4.setBrush(QPalette::Disabled, QPalette::Button, brush);
    btnbrowsedoc->setPalette(palette4);
    btnbrowsedoc->setAutoFillBackground(true);
    btnbrowsedoc->setIcon(QIcon(QString::fromUtf8(":/images/images/wordprocessing.png")));
    btnbrowsedoc->setCheckable(false);
    btnbrowsedoc->setFlat(true);
    btnnewdoc = new QPushButton(page_4);
    btnnewdoc->setObjectName(QString::fromUtf8("btnnewdoc"));
    btnnewdoc->setGeometry(QRect(10, 40, 251, 27));
    QPalette palette5;
    palette5.setBrush(QPalette::Active, QPalette::Button, brush);
    palette5.setBrush(QPalette::Inactive, QPalette::Button, brush);
    palette5.setBrush(QPalette::Disabled, QPalette::Button, brush);
    btnnewdoc->setPalette(palette5);
    btnnewdoc->setAutoFillBackground(true);
    btnnewdoc->setIcon(QIcon(QString::fromUtf8(":/images/images/wordprocessing.png")));
    btnnewdoc->setCheckable(false);
    btnnewdoc->setFlat(true);
    maintoolbox->addItem(page_4, QIcon(QString::fromUtf8(":/images/images/wordprocessing.png")), QApplication::translate("mainfrm", "Documents", 0, QApplication::UnicodeUTF8));
    page_5 = new QWidget();
    page_5->setObjectName(QString::fromUtf8("page_5"));
    page_5->setGeometry(QRect(0, 0, 96, 26));
    maintoolbox->addItem(page_5, QIcon(QString::fromUtf8(":/images/images/kcalc.png")), QApplication::translate("mainfrm", "Finances", 0, QApplication::UnicodeUTF8));
    page_6 = new QWidget();
    page_6->setObjectName(QString::fromUtf8("page_6"));
    page_6->setGeometry(QRect(0, 0, 96, 26));
    maintoolbox->addItem(page_6, QIcon(QString::fromUtf8(":/images/images/message.png")), QApplication::translate("mainfrm", "Messages", 0, QApplication::UnicodeUTF8));
    page_7 = new QWidget();
    page_7->setObjectName(QString::fromUtf8("page_7"));
    page_7->setGeometry(QRect(0, 0, 96, 26));
    maintoolbox->addItem(page_7, QIcon(QString::fromUtf8(":/images/images/logo.png")), QApplication::translate("mainfrm", "Various", 0, QApplication::UnicodeUTF8));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    page->setGeometry(QRect(0, 0, 96, 26));
    groupBox_2 = new QGroupBox(page);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setGeometry(QRect(0, 0, 311, 111));
    label_2 = new QLabel(groupBox_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 50, 111, 20));
    label_3 = new QLabel(groupBox_2);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(10, 80, 111, 20));
    lbldb = new QLabel(groupBox_2);
    lbldb->setObjectName(QString::fromUtf8("lbldb"));
    lbldb->setGeometry(QRect(140, 50, 161, 20));
    lblserver = new QLabel(groupBox_2);
    lblserver->setObjectName(QString::fromUtf8("lblserver"));
    lblserver->setGeometry(QRect(140, 80, 161, 20));
    label = new QLabel(groupBox_2);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 20, 111, 20));
    lbluser = new QLabel(groupBox_2);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));
    lbluser->setGeometry(QRect(140, 20, 161, 20));
    maintoolbox->addItem(page, QIcon(QString::fromUtf8(":/images/images/xmag.png")), QApplication::translate("mainfrm", "Information", 0, QApplication::UnicodeUTF8));
    mainfrm->setCentralWidget(centralwidget);

    retranslateUi(mainfrm);
    QObject::connect(btnexit, SIGNAL(released()), mainfrm, SLOT(close()));

    maintoolbox->setCurrentIndex(3);


    QMetaObject::connectSlotsByName(mainfrm);
    } // setupUi

    void retranslateUi(QMainWindow *mainfrm)
    {
    mainfrm->setWindowTitle(QApplication::translate("mainfrm", "first", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QString());
    btnsettings->setText(QApplication::translate("mainfrm", "&Settings", 0, QApplication::UnicodeUTF8));
    lblmsg->setText(QApplication::translate("mainfrm", "-", 0, QApplication::UnicodeUTF8));
    btnabout->setText(QApplication::translate("mainfrm", "&About", 0, QApplication::UnicodeUTF8));
    btnexit->setText(QApplication::translate("mainfrm", "&Exit", 0, QApplication::UnicodeUTF8));
    btnbrowsedir->setText(QApplication::translate("mainfrm", "Browse Directories", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page_1), QApplication::translate("mainfrm", "Directories", 0, QApplication::UnicodeUTF8));
    btnvieworders->setText(QApplication::translate("mainfrm", "View purchase orders", 0, QApplication::UnicodeUTF8));
    btninventory->setText(QApplication::translate("mainfrm", "Make inventory", 0, QApplication::UnicodeUTF8));
    btnbrowsedata->setText(QApplication::translate("mainfrm", "Browse Tables", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page_2), QApplication::translate("mainfrm", "Datatables", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page_3), QApplication::translate("mainfrm", "Procedures", 0, QApplication::UnicodeUTF8));
    btnbrowsedoc->setText(QApplication::translate("mainfrm", "Browse documents", 0, QApplication::UnicodeUTF8));
    btnnewdoc->setText(QApplication::translate("mainfrm", "New document", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page_4), QApplication::translate("mainfrm", "Documents", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page_5), QApplication::translate("mainfrm", "Finances", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page_6), QApplication::translate("mainfrm", "Messages", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page_7), QApplication::translate("mainfrm", "Various", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QString());
    label_2->setText(QApplication::translate("mainfrm", "Database:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("mainfrm", "Server:", 0, QApplication::UnicodeUTF8));
    lbldb->setText(QApplication::translate("mainfrm", "-", 0, QApplication::UnicodeUTF8));
    lblserver->setText(QApplication::translate("mainfrm", "-", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("mainfrm", "Username:", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("mainfrm", "-", 0, QApplication::UnicodeUTF8));
    maintoolbox->setItemText(maintoolbox->indexOf(page), QApplication::translate("mainfrm", "Information", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(mainfrm);
    } // retranslateUi

};

namespace Ui {
    class mainfrm: public Ui_mainfrm {};
} // namespace Ui

#endif // UI_MAINFRM_H
