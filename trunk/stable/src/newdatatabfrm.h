#ifndef NEWDATATABFRM_H
#define NEWDATATABFRM_H
//
#include "ui_newdatatabfrm.h"
//
class newdatatabfrm : public QDialog, public Ui::newdatatabfrm
{
Q_OBJECT
public:
	newdatatabfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
public:
	void init();
private slots:
	void on_btnadd_released();
	void on_btnremove_released();
	void on_btnup_released();
	void on_btndown_released();
	void change_rdb();
	void createtable();
};
#endif





