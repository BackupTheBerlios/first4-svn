#ifndef LOGINCONFSERVERSFRM_H
#define LOGINCONFSERVERSFRM_H
//
#include <QDialog>
#include "ui_loginconfserversfrm.h"
//
class loginconfserversfrm : public QDialog, public Ui::loginconfserversfrm
{
Q_OBJECT
public:
	loginconfserversfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private:
	void loadservers();
private slots:
	void addservers();
	void delservers();
};
#endif





