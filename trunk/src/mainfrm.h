#ifndef MAINFRM_H
#define MAINFRM_H
//
#include "ui_mainfrm.h"
//
class mainfrm : public QMainWindow, public Ui::mainfrm
{
Q_OBJECT
public:
	mainfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void closeEvent( QCloseEvent* ce );
	void about();
	void browseaddr();
	void browsedata();
	void vieworders();
	void inventory();
	void opendoc();
	void newdoc();
	void browseorders();
	void neworder();
	void browseaccounts();
	void browsemsgs();
	void newmsg();
	void addrimpexp();
private:
	void cleanup();
	void admtasks();
public:
	void loaduserdata();
	void initplugins();
public slots:
	void checkmsg();	
	void config();
};
#endif






