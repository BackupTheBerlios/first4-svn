#ifndef ADDRFRM_H
#define ADDRFRM_H
//
#include "ui_addrfrm.h"
//
class addrfrm : public QWidget, public Ui::addrfrm
{
Q_OBJECT
public:
	addrfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void closeEvent( QCloseEvent* ce );
	void loadaddrdetail();
	void loadaddrs();
	void loaddocsdata();
	void openauftrag();
	void changecust1();
	void changecust2();
	void changecust3();
	void changecust4();
	void changecust5();
	void newaddr();
	void saveaddr();
	void deladdr();
	void clearsearch();
	void search();
	void printaddr();
	void opendoc();
	void deletedoc();
	void contmenu();
	void contmenuaddr();
	void moveaddr(QString dest);
	void impexp();
public:
	void init();
	void checkrights();
	void loaddocs(QString);
	void loadauftr(QString);
	void copyaddr(QString dest);
private:
	QString writetexfile();
	QString loadtemplatedata();
};
#endif
