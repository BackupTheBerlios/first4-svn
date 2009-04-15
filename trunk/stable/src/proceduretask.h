#ifndef PROCEDURETASK_H
#define PROCEDURETASK_H
//
#include "ui_proceduretask.h"
//
class proceduretask : public QDialog, public Ui::proceduretask
{
Q_OBJECT
public:
	proceduretask( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif





