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
	QString getaddress();
	QString getrabatt();
public slots:
	void searchaddress();
private slots:
	void clearsearch();
};
#endif





