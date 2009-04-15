#ifndef DOCCOMPLETEFRM_H
#define DOCCOMPLETEFRM_H
//
#include "ui_doccompletefrm.h"
//
class doccompletefrm : public QDialog, public Ui::doccompletefrm
{
Q_OBJECT
public:
	doccompletefrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
public slots:
	void init();
	void acceptdata();
};
#endif





