#ifndef STOCKSELFRM_H
#define STOCKSELFRM_H
//
#include "ui_stockselfrm.h"
//
class stockselfrm : public QDialog, public Ui::stockselfrm
{
Q_OBJECT
public:
	stockselfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
	void init();
private slots:
	void acceptentry();
	void keyReleaseEvent(QKeyEvent* e);
};
#endif





