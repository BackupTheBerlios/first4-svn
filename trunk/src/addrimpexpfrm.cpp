#include "addrimpexpfrm.h"
//
addrimpexpfrm::addrimpexpfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void addrimpexpfrm::init()
{
	this->setFixedSize(this->width(), this->height());
	mainstack->setCurrentIndex(0);
	
	connect(btncancel, SIGNAL(released()), this, SLOT(reject()));
	connect(btnnext, SIGNAL(released()), this, SLOT(next()));
	connect(btnback, SIGNAL(released()), this, SLOT(back()));
	connect(btnexpcsvload, SIGNAL(released()), this, SLOT(loaddir_expcsv()));
	
	loadcolumns();
}
//
void addrimpexpfrm::loadcolumns()
{
		
}
//
void addrimpexpfrm::next()
{
	if(rbtn1->isChecked())
		mainstack->setCurrentIndex(1);
	else if(rbtn2->isChecked())
		mainstack->setCurrentIndex(2);
	else if(rbtn3->isChecked())
		mainstack->setCurrentIndex(3);
	else if(rbtn4->isChecked())
		mainstack->setCurrentIndex(4);
}
//
void addrimpexpfrm::back()
{
	mainstack->setCurrentIndex(0);
}
void addrimpexpfrm::loaddir_expcsv()
{
	
}
