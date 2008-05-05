#ifndef ACCOUNTSFRM_H
#define ACCOUNTSFRM_H
//
#include "ui_accountsfrm.h"
//
class accountsfrm : public QWidget, public Ui::accountsfrm
{
Q_OBJECT
public:
	accountsfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	int init();
private slots:
	void loaddetails();
	void contmenu();
	void newentry();
	void editentry();
	void deleteentry();
	void print();
	void datatransfer();
	void completeitems();
private:
	void closeEvent( QCloseEvent* ce );
	void initindexlist();
	void inittreemainaccounts();
	void inittreemainoverview();
	void initmaintreeincexp();
	void loadaccounts();
	void loadaccountdata(QString ID);
	void loadarchivdata(QString type);
	void loadincexpdata(QString type);
	QString calctotal(int type);
	void writetexfile(int type);
	void esrimport();
	void csvexport();
	void mt940import();
	QString loadtemplatedata();
};
#endif





