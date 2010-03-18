#ifndef ACCOUNTSCOMPLFRM_H
#define ACCOUNTSCOMPLFRM_H
//
#include "ui_accountscomplfrm.h"
//
class accountscomplfrm : public QDialog, public Ui::accountscomplfrm
{
Q_OBJECT
public:
	accountscomplfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private slots:
};
#endif





