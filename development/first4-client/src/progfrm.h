#ifndef PROGFRM_H
#define PROGFRM_H
//
#include "ui_progfrm.h"
//
class progfrm : public QWidget, public Ui::progfrm
{
Q_OBJECT
public:
	progfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif





