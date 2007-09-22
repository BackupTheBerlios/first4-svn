#include "dbwizzardfrm.h"
//
dbwizzardfrm::dbwizzardfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void dbwizzardfrm::init()
{
	connect(rbtnmysqlex, SIGNAL(clicked()), this, SLOT(enable_next()));
	connect(rbtnmysqlnew, SIGNAL(clicked()), this, SLOT(enable_next()));
}
//
void dbwizzardfrm::next()
{
	
}
//
void dbwizzardfrm::previous()
{
	
}
void dbwizzardfrm::enable_next()
{
	btnnext->setEnabled(TRUE);
}
//
