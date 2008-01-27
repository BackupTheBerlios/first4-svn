#ifndef INVFRM_H
#define INVFRM_H
//
#include "ui_invfrm.h"
//
class invfrm : public QWidget, public Ui::invfrm
{
Q_OBJECT
public:
	invfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	int init();
	int checkrights();
	void writetexfile();
private slots:
	void closeEvent( QCloseEvent* ce );
public slots:
	void setchange();
	void loadinv();
	void print();
	void printpreview();
	void complete();
	void newinv();
	void viewcomments();
	void savedata();
	void loaddata();
private:
	QString loadtemplatedata();
};
#endif
