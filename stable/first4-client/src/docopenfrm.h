#ifndef DOCOPENFRM_H
#define DOCOPENFRM_H
//
#include "ui_docopenfrm.h"
//
class docopenfrm : public QWidget, public Ui::docopenfrm
{
Q_OBJECT
public:
	docopenfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private:
	void closeEvent( QCloseEvent* ce );
private slots:
	void adressbtnonoff();
	void loaddocs();
	void loaddocsdetails();
	void deletedoc();
	void newdoc();
	void editdoc();
	void print();
	void searchdoc();
	void clearsearch();
	void openseladressfrm();
};
#endif





