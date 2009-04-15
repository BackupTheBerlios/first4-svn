#ifndef MSGFRM_H
#define MSGFRM_H
//
#include "ui_msgfrm.h"
//
class msgfrm : public QWidget, public Ui::msgfrm
{
Q_OBJECT
public:
	msgfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private:
	void closeEvent(QCloseEvent* ce );
	void loadmsgcfg();
	void printalllist();
	void printall();
	void printsellist();
	void printsel();
private slots:
	void loadmsg();
	void initmainlistview(QString art);
	void editmsg();
	void deletemsg();
	void contmenu();
	void completeitems();
	void print();
public slots:
	void newmsg();
};
#endif






