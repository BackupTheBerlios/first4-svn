#ifndef DATAFRM_H
#define DATAFRM_H
//
#include "ui_datafrm.h"
//
class datafrm : public QWidget, public Ui::datafrm
{
Q_OBJECT
public:
	datafrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
	void checkrights();
	void searchdata();
	void searchstock();
private slots:
	void changecmb();
	void loadstock();
	void loaddata();
	void savetable();
	void navtable();
    void closeEvent( QCloseEvent* ce );
    void newstockentry();
    void editstockentry();
    void delstockentry();
    void print();
    void contmenudata();
    void contmenustock();
    void removerow();
    void searchentries();
    void clearsearch();
    void impexp();
private:
	QString loadtemplatedata();
	void writetexfile(int);
};
#endif





