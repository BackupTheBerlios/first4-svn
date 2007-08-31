#include "proceduresearch.h"
//
proceduresearch::proceduresearch( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//
void proceduresearch::init()
{
	treemain->setColumnWidth(0, 150);
    treemain->setColumnWidth(1, 80);
    treemain->setColumnWidth(2, 0);
    treemain->setColumnWidth(3, 190);
    treemain->setColumnWidth(4, 300);
    treemain->setColumnWidth(5, 80);
}
//
void proceduresearch::searchentry()
{/*
    int i;
    QStringList searchrow;
    searchrow << "orderid" << "client" << "description" << "tasks" << "orders";
    
    // Active orders
    for(i=0;i<6;i++)
    {
    	
    	QTreeWidgetItem *item = treeindex->topLevelItem(i);
		QString qstr1 = QString("SELECT ID FROM proceduretab WHERE `status` = '%1' AND `%2` LIKE '%%3%';").arg(i, 0, 10).arg(searchrow[cmbsearchrow->currentIndex()]).arg(txtsearch->text());
		QSqlQuery query1(qstr1);
		if(query1.isActive())
		    item->setText(1, QString("%1").arg(query1.size(), 0, 10));
    }
    
    //Archived orders 
	QTreeWidgetItem* archiveitem = treeindex->topLevelItem(6);
	QString qstr2 = QString("SELECT ID FROM procedurearchiv WHERE `status` = '%1' AND `%2` LIKE '%%3%';").arg(i, 0, 10).arg(searchrow[cmbsearchrow->currentIndex()]).arg(txtsearch->text());
	QSqlQuery query2(qstr2);
	if(query2.isActive())
	    archiveitem->setText(1, QString("%1").arg(query2.size(), 0, 10));
*/}
//
