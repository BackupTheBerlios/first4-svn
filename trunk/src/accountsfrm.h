#ifndef ACCOUNTSFRM_H
#define ACCOUNTSFRM_H
//
#include "ui_accountsfrm.h"
//
class accountsfrm : public QWidget, public Ui::accountsfrm
{
Q_OBJECT
public:
	accountsfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	int init();
private slots:
};
#endif





