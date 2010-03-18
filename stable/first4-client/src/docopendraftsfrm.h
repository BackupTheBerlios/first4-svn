#ifndef DOCOPENDRAFTSFRM_H
#define DOCOPENDRAFTSFRM_H
//
#include "ui_docopendraftfrm.h"
//
class docopendraftsfrm : public QDialog, public Ui::docopendraftsfrm
{
Q_OBJECT
private:
	void readdoctab();
public:
	docopendraftsfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void loaddocs();
	void loaddocsdetails();
	void close_accept();
	void searchdoc();
	void clearsearch();
	void openseladdressfrm();
	void adressbtnonoff();
public slots:
	void init();
};
#endif





