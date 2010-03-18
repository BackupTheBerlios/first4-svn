#ifndef DBUPDATEFRM_H
#define DBUPDATEFRM_H
//
#include <QDialog>
#include "ui_dbupdatefrm.h"
//
class dbupdatefrm : public QDialog, public Ui::dbupdatefrm
{
Q_OBJECT
public:
	dbupdatefrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	int init();
private slots:
	void check_db_structure();
	void update_db_structure(QString section);
};
#endif
