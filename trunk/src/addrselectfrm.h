#ifndef ADDRSELECTFRM_H
#define ADDRSELECTFRM_H
//
#include "ui_addrselectfrm.h"
//
class addrselectfrm : public QDialog, public Ui::addrselectfrm
{
Q_OBJECT
public:
	addrselectfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
	QString getadress();
	QString getrabatt();
private slots:
	void searchaddress();
	void clearsearch();
};
#endif





