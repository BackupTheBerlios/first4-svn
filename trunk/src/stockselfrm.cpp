#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCloseEvent>
#include <QMessageBox>
#include <QKeyEvent>
//
#include "stockselfrm.h"
#include "vars.h"
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

	int i;
	vars v;
	QStringList colwidth = v.loadcolwidth(this->objectName(), "treemain" );
	if ( colwidth.size() > 0	)
	{
		for(i=0; i<colwidth.size(); i++)
			treemain->setColumnWidth(i, colwidth[i].toInt());
	}

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
	int cols;
	QStringList colwidth;
	for(cols=0; cols < treemain->columnCount(); cols++)
			colwidth << QString("%1").arg(treemain->columnWidth(cols));
	vars v;
	v.savecolwidth(this->objectName(), "treemain", colwidth);
	this->accept();
}
