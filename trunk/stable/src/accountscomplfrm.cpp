#include "accountscomplfrm.h"
//
accountscomplfrm::accountscomplfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void accountscomplfrm::init()
{
	this->setFixedSize(this->width(), this->height());
}
