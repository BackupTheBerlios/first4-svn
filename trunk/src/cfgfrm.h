#ifndef CFGFRM_H
#define CFGFRM_H
//
#include "ui_cfgfrm.h"
//
class cfgfrm : public QWidget, public Ui::cfgfrm
{
Q_OBJECT
public:
	cfgfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
public:
	void initfrm();
	QString cryptpwd(QString pwd);
	void loadlangfile();
	void loaddbinfo();
	void loadservers();
	void closeEvent(QCloseEvent* ce );
	void applydbspec();
	void loadusers();
	void loadressources();
	void loadsettings();
	void loadowndata();
public slots:
	void changepwd();
	void selectlangfile();
	void addservers();
	void delservers();
	void opendbspec();
	void selectuser();
	void newuser();
	void saveuserchange();
	void loadressourcesdetails();
	void seldoctemplate();
	void applyresourcesdetails();
	void saveresourcesdetails();
	void contmenu();
	void newaddr();
	void newdata();
	void newaccount();
	void rentab();
 	void deltab();
	void selectdocpath();
	void selecttemplpath();
	void savedefaultpath();
	void savesettings();
	void saveowndata();
};
#endif





