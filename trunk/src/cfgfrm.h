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
	void init();
	QString cryptpwd(QString pwd);
	void loadlangfile();
	void loaddbinfo();
	void loadservers();
	void closeEvent(QCloseEvent* ce );
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
	void canceluser();
	void deluser();
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
	void load_local_tools();
	void load_db_tools();
	void save_local_tools();
	void save_db_tools();
private slots:
	void tools_filedialog();
	void applydbspec();
	void templates_load();
	void templates_new();
	void templates_edit();
	void templates_delete();
	void templates_loaddetails();
};
#endif





