#include "stockselfrm.h"
//
stockselfrm::stockselfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void stockselfrm::init()
{
		treemain->hideColumn(0);
		treemain->hideColumn(7);
		treemain->hideColumn(8);
}
