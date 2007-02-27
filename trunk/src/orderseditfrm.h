#ifndef ORDERSEDITFRM_H
#define ORDERSEDITFRM_H
//
#include "ui_orderseditfrm.h"
//
class orderseditfrm : public QDialog, public Ui::orderseditfrm
{
Q_OBJECT
public:
	orderseditfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private slots:
	void newentry();
	void updentry();
public slots:
	void editentry(QString ID);
	void changeprice();
	void clearstock();
	void checkstock();
};
#endif







