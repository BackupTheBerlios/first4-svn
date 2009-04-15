#ifndef PRINTFRM_H
#define PRINTFRM_H
//
#include "ui_printfrm.h"
//
class printfrm : public QDialog, public Ui::printfrm
{
Q_OBJECT
public:
	printfrm( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif





