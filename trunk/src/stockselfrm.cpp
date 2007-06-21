#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCloseEvent>
#include <QMessageBox>
//
#include "stockselfrm.h"
#include "vars.h"
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
