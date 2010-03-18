#ifndef PROCEDURESEARCH_H
#define PROCEDURESEARCH_H
//
#include "ui_proceduresearch.h"
//
class proceduresearch : public QDialog, public Ui::proceduresearch
{
Q_OBJECT
public:
	proceduresearch( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
public slots:
	void searchentry();
	void clearsearch();
private slots:
	void acceptbtn();
	void cancelbtn();
private:
	void closeEvent( QCloseEvent* ce );	
};
#endif





