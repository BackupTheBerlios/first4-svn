#ifndef DATAEDITFRM_H
#define DATAEDITFRM_H
//
#include "ui_dataeditfrm.h"
//
class dataeditfrm : public QDialog, public Ui::dataeditfrm
{
Q_OBJECT
public:
	dataeditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
	void loadvat();
	void loadentry(QString);
	void newentry();
	void updateentry();
public slots:
	void calc_gw();
	void acceptdata();
	void seladdress();
	void contmenu();
	void acceptsp();
	void removerow();
	void addrow();
private:
	void reject();
};
#endif
