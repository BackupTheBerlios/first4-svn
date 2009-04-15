#ifndef ORDERSFRM_H
#define ORDERSFRM_H
//
#include "ui_ordersfrm.h"
//
class ordersfrm : public QWidget, public Ui::ordersfrm
{
Q_OBJECT
public:
	ordersfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	int init();
	void countentries();
	int checkrights();
public slots:
	void loadentries();
	void newentry();
	void editentry();
	void deleteentry();
	void complete();
	void contmenu();
private:
	void closeEvent( QCloseEvent* ce );
private slots:
};
#endif





