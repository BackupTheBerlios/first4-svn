#ifndef LOGINFRM_H
#define LOGINFRM_H
//
#include "ui_loginfrm.h"
//
class loginfrm : public QDialog, public Ui::loginfrm
{
Q_OBJECT
public:
	loginfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
public:
	bool loadservers();
	void saveservers();
	void loadsysvars();
	void init();
private slots:
	void configure_servers();
public slots:
	void checkpwd();
};
#endif





