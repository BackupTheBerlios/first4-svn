#ifndef PROCEDUREEDITFRM_H
#define PROCEDUREEDITFRM_H
//
#include "ui_procedureeditfrm.h"
//
class procedureeditfrm : public QDialog, public Ui::procedureeditfrm
{
Q_OBJECT
public:
	procedureeditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
	void neworder();
private:
	void initvat();
private slots:
	void searchaddress();
	void clearaddress();
	void acceptdata();
	void checkdb();
	void contmenu();
	void edittask();
	void removerow();
	void editorder();
public slots:
	void navtasktab(int row);
	void navordertabs(int row);
};
#endif






