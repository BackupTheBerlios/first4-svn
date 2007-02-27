#ifndef NEWDBFRM_H
#define NEWDBFRM_H
//
#include "ui_newdbfrm.h"
//
class newdbfrm : public QDialog, public Ui::newdbfrm
{
Q_OBJECT
public:
	newdbfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
public:
	void init();
public slots:
	void checkdatabases();
	void writeconffile();
};
#endif
