#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCloseEvent>
#include <QMessageBox>
//
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
		
	int i;
    QString tmpstr;
    QStringList lines;
    QFile file(QDir::homePath()+"/.first4/columns.conf");
    if(file.open(QIODevice::ReadOnly))
    {
		QTextStream stream(&file);
		while(!stream.atEnd())
		{
		    tmpstr = stream.readLine();
		    if(tmpstr.section("-", 0, 0) == this->objectName())
		    {
		    	for(i=0; i<tmpstr.count(";"); i++)
		    		treemain->setColumnWidth(i, tmpstr.section("-", 1, 1).section(";", i, i).toInt());
	    	}
		}
		file.close();    
    }
    
    connect(btnaccept, SIGNAL(released()), this, SLOT(acceptentry()));
    connect(treemain, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(acceptentry()));
}
//
void stockselfrm::acceptentry()
{
	int cols;
    QFile file(QDir::homePath()+"/.first4/columns.conf" );
    if(file.open(QIODevice::WriteOnly))
    {
		QTextStream stream(&file);
		stream << this->objectName() << "-";
		for(cols=0; cols < treemain->columnCount(); cols++)
			stream << treemain->columnWidth(cols) << ";";
		file.close();    
    }
	this->accept();
}
