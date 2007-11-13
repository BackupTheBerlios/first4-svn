#ifndef DBWIZZARDFRM_H
#define DBWIZZARDFRM_H
//
#include "ui_dbwizzardfrm.h"
//
class dbwizzardfrm : public QDialog, public Ui::dbwizzardfrm
{
Q_OBJECT
public:
	dbwizzardfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private slots:
	void next();
	void back();
	void enable_next();
	void checkdbs();
private:
	void writeconffile();
	void createnewmysql();
};
#endif
