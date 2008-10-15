#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCloseEvent>
#include <QMessageBox>
#include <QKeyEvent>
//
#include "stockselfrm.h"
//
bool first_key = false;
//
stockselfrm::stockselfrm( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void stockselfrm::init()
{
	first_key = false;
	
	treemain->hideColumn(0);
	treemain->hideColumn(7);
	treemain->hideColumn(8);
	treemain->hideColumn(9);

	connect(btnaccept, SIGNAL(released()), this, SLOT(acceptentry()));
	connect(treemain, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(acceptentry()));
	connect(treemain, SIGNAL(keyReleaseEvent(QKeyEvent*)), this, SLOT(keyReleaseEvent(QKeyEvent *)));
}
//
void stockselfrm::keyReleaseEvent(QKeyEvent* e){
	if(first_key && e->key() == 16777220) //Check if Enter is pressed
	{
		this->acceptentry();
	}
	first_key = true;
} 
//
void stockselfrm::acceptentry()
{
	this->accept();
}
