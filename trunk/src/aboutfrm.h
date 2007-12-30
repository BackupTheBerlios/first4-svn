#ifndef ABOUTFRM_H
#define ABOUTFRM_H
//
#include "ui_aboutfrm.h"
//
class aboutfrm : public QDialog, public Ui::aboutfrm
{
Q_OBJECT
public:
	aboutfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
};
#endif






